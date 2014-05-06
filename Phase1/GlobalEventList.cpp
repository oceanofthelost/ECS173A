#include<queue>
#include "Event.h"
#include "GlobalEventList.h"
using namespace std;

/**
 * Default constructor for the global event list
 */
GlobalEventList::GlobalEventList()
{
   GEL = priority_queue<Event>(); 
}

/**
 * adds an event to the global event list
 * @param passed: event that is added to global event list
 */
void GlobalEventList::addEvent(const Event& passed)
{
    GEL.push(passed);
}

/**
 * returns next event
 * @return: event that will occur next
 */
Event GlobalEventList::nextEvent()
{
    Event returned = GEL.top();
    GEL.pop();
    return returned;
}
