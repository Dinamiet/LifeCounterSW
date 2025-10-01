#include "battery.h"
#include "i2c.h"

BQ27441 batteryFuelGauge;

typedef struct _I2CDevice_
{
	I2C_HandleTypeDef* Handle;
	uint8_t            DeviceID;
} I2CDevice;

static I2CDevice batteryDevice;

static size_t batteryFuelGauge_Read(const BQ27441Device* device, const BQ27441Address address, void* data, const size_t size);
static size_t batteryFuelGauge_Write(const BQ27441Device* device, const BQ27441Address address, const void* data, const size_t size);

void Battery_Setup()
{
	batteryDevice.Handle   = &hi2c1;
	batteryDevice.DeviceID = 0x55 << 1;
	BQ27441_Init(&batteryFuelGauge, &batteryDevice, batteryFuelGauge_Read, batteryFuelGauge_Write);

	BQ27441Flags flags;
	BQ27441_Flags(&batteryFuelGauge, &flags);

	if (flags.ResetOccured)
	{
		BQ27441Status status;
		if (!BQ27441_Status(&batteryFuelGauge, &status))
			return;
		if (status.Sealed)
			if (!BQ27441_Unseal(&batteryFuelGauge))
				return;
		if (!flags.ConfigUpdateMode)
		{
			if (!BQ27441_EnterMode(&batteryFuelGauge, BQ27441_MODE_CONFIGURE))
				return;

			do {
				if (!BQ27441_Flags(&batteryFuelGauge, &flags))
					return;
			} while (!flags.ConfigUpdateMode);
		}

		if (!BQ27441_Configure(&batteryFuelGauge, DEFAULT_CAPACITY, DEFAULT_TERMINATE_VOLTAGE, DEFAULT_TAPER_CURRENT))
			return;

		BQ27441_SoftReset(&batteryFuelGauge);
	}
}

static size_t batteryFuelGauge_Read(const BQ27441Device* _device, const BQ27441Address address, void* data, const size_t size)
{
	I2CDevice* device = (I2CDevice*)_device;
	switch (address.Mode)
	{
		case ADDRESS_MEMORY_NO_ADDRESS:
			if (HAL_I2C_Master_Receive(device->Handle, device->DeviceID, data, size, HAL_MAX_DELAY) == HAL_OK)
				return size;
			break;

		default:
			if (HAL_I2C_Mem_Read(device->Handle, device->DeviceID, address.Memory, address.Mode, data, size, HAL_MAX_DELAY) == HAL_OK)
				return size;
			break;
	}

	return 0;
}

static size_t batteryFuelGauge_Write(const BQ27441Device* _device, const BQ27441Address address, const void* data, const size_t size)
{
	I2CDevice* device = (I2CDevice*)_device;
	switch (address.Mode)
	{
		case ADDRESS_MEMORY_NO_ADDRESS:
			if (HAL_I2C_Master_Transmit(device->Handle, device->DeviceID, (uint8_t*)data, size, HAL_MAX_DELAY) == HAL_OK)
				return size;
			break;

		default:
			if (HAL_I2C_Mem_Write(device->Handle, device->DeviceID, address.Memory, address.Mode, (uint8_t*)data, size, HAL_MAX_DELAY) == HAL_OK)
				return size;
			break;
	}

	return 0;
}
