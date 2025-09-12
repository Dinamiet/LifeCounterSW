#include "player1.h"

#include "utilities.h"
#include "events.h"

#include "handlers.h"

ObserverSubscription knobIncSub;
ObserverSubscription knobDecSub;
ObserverSubscription btnSub;

void Player1_Setup()
{
	Observer_Subscribe(&eventNotifier, &knobIncSub, EVENT_KNOB_1_INC, knobIncrement);
	Observer_Subscribe(&eventNotifier, &knobDecSub, EVENT_KNOB_1_DEC, knobDecrement);
	Observer_Subscribe(&eventNotifier, &btnSub, EVENT_BUTTON_1_PRESS, buttonEvent);
}
