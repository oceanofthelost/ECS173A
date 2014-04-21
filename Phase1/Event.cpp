#include "Event.h"

Event::Event(double t,EventType type)
{
    time = t;
    event_type = type;
}

bool Event::operator<(const Event& E) const
{
    return time > E.time;
}

EventType Event::getEventType() const
{
    return event_type;
}

double Event::getTime() const
{
    return time;
}
