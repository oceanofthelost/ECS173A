#include "Event.h"

/**
 *  Default constructor for an Event
 */
Event::Event(double t,EventType type)
{
    time = t;
    event_type = type;
}

/**
 * Operator used for priority queue
 * @param E: Event that we are going to compare
 * @return: true if self is is greater than E. false if 
 * 			E is less than self  
 */
bool Event::operator<(const Event& E) const
{
    return time > E.time;
}

/**
 * Finds out what type of event the Event is
 * @return: enum type that represents the event type
 */
EventType Event::getEventType() const
{
    return event_type;
}

/**
 * Finds the time of the event
 * @return: time the event has
 */
double Event::getTime() const
{
    return time;
}
