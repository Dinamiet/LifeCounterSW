#include "player1.h"

#include "utilities.h"
#include "events.h"

#include "handlers.h"

ObserverSubscription knobIncSub2;
ObserverSubscription knobDecSub2;
ObserverSubscription btnSub2;

void Player2_Setup()
{
	Observer_Subscribe(&eventNotifier, &knobIncSub2, EVENT_KNOB_2_INC, knobIncrement2);
	Observer_Subscribe(&eventNotifier, &knobDecSub2, EVENT_KNOB_2_DEC, knobDecrement2);
	Observer_Subscribe(&eventNotifier, &btnSub2, EVENT_BUTTON_2_PRESS, buttonEvent2);
}
