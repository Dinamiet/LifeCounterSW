#include "buzzer.h"

#include "utilities.h"

#include "events.h"
#include "buzz.h"

ObserverSubscription knob1IncBuzzSub;
ObserverSubscription knob1DecBuzzSub;
ObserverSubscription knob2IncBuzzSub;
ObserverSubscription knob2DecBuzzSub;
ObserverSubscription btn1BuzzSub;
ObserverSubscription btn2BuzzSub;

void Buzzer_Setup()
{
	Observer_Subscribe(&eventNotifier, &knob1IncBuzzSub, EVENT_KNOB_1_INC, buzzerBuzz);
	Observer_Subscribe(&eventNotifier, &knob1DecBuzzSub, EVENT_KNOB_1_DEC, buzzerBuzz);
	Observer_Subscribe(&eventNotifier, &btn1BuzzSub, EVENT_BUTTON_1_PRESS, buzzerBuzz);

	Observer_Subscribe(&eventNotifier, &knob2IncBuzzSub, EVENT_KNOB_2_INC, buzzerBuzz);
	Observer_Subscribe(&eventNotifier, &knob2DecBuzzSub, EVENT_KNOB_2_DEC, buzzerBuzz);
	Observer_Subscribe(&eventNotifier, &btn2BuzzSub, EVENT_BUTTON_2_PRESS, buzzerBuzz);
}
