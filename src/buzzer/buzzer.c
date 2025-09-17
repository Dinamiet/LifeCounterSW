#include "buzzer.h"

#include "buzz.h"
#include "events.h"
#include "utilities.h"

static ObserverSubscription knobBuzzSub;
static ObserverSubscription btnBuzzSub;

void Buzzer_Setup()
{
	Observer_Subscribe(&eventNotifier, &knobBuzzSub, EVENT_KNOB, buzzerBuzz);
	Observer_Subscribe(&eventNotifier, &btnBuzzSub, EVENT_BUTTON, buzzerBuzz);
}
