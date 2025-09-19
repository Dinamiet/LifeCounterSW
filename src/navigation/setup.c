
#include "counter.h"
#include "mode.h"
#include "navigation.h"
#include "setting.h"
#include "trigger.h"

void Navigation_Setup()
{
	Trigger_Setup();
	Counter_Init();
	Setting_Init();

	Mode_Setup();
}
