#include "battery.h"
#include "bq27441.h"
#include "i2c.h"

BQ27441 batteryFuelGauge;

typedef struct _I2CDevice_
{
	I2C_HandleTypeDef* Handle;
	uint8_t            DeviceID;
} I2CDevice;

static I2CDevice batteryDevice;

static size_t batteryFuelGauge_Read(const I2CDevice* device, void* data, const size_t size);
static size_t batteryFuelGauge_Write(const I2CDevice* device, const void* data, const size_t size);
static size_t batteryFuelGauge_MemRead(const I2CDevice* device, uint8_t address, void* data, const size_t size);
static size_t batteryFuelGauge_MemWrite(const I2CDevice* device, const uint8_t address, const void* data, const size_t size);

void Battery_Setup()
{
	batteryDevice.Handle   = &hi2c1;
	batteryDevice.DeviceID = 0x55 << 1;
	BQ27441_Init(&batteryFuelGauge, &batteryDevice, batteryFuelGauge_Read, batteryFuelGauge_Write, batteryFuelGauge_MemRead, batteryFuelGauge_MemWrite);
}

uint16_t Battery_Temperature()
{
	uint16_t rawTemp;
	BQ27441_Temperature(&batteryFuelGauge, BQ27441_TEMPERATURE_INTERNAL, &rawTemp);
	return (rawTemp/10)-273;
}

uint16_t Battery_SOC()
{
	uint16_t soc;
	BQ27441_StateOfCharge(&batteryFuelGauge, &soc);
	return soc;
}

int16_t Battery_Current()
{
	int16_t current;
	BQ27441_Current(&batteryFuelGauge, BQ27441_CURRENT_AVG, &current);
	return current;
}

uint16_t Battery_Capacity()
{
	uint16_t cap;
	BQ27441_Capacity(&batteryFuelGauge, BQ27441_CAPACITY_FULL_COMPENSATED, &cap);
	return cap;
}

static size_t batteryFuelGauge_Read(const I2CDevice* device, void* data, const size_t size)
{
	if (HAL_I2C_Master_Receive(device->Handle, device->DeviceID, data, size, HAL_MAX_DELAY) == HAL_OK)
		return size;

	return 0;
}

static size_t batteryFuelGauge_Write(const I2CDevice* device, const void* data, const size_t size)
{
	if (HAL_I2C_Master_Transmit(device->Handle, device->DeviceID, (uint8_t*)data, size, HAL_MAX_DELAY) == HAL_OK)
		return size;

	return 0;
}

static size_t batteryFuelGauge_MemRead(const I2CDevice* device, uint8_t address, void* data, const size_t size)
{
	if (HAL_I2C_Mem_Read(device->Handle, device->DeviceID, address, sizeof(address), data, size, HAL_MAX_DELAY) == HAL_OK)
		return size;

	return 0;
}

static size_t batteryFuelGauge_MemWrite(const I2CDevice* device, const uint8_t address, const void* data, const size_t size)
{
	if (HAL_I2C_Mem_Write(device->Handle, device->DeviceID, address, sizeof(address), (uint8_t*)data, size, HAL_MAX_DELAY) == HAL_OK)
		return size;

	return 0;
}
