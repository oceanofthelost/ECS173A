#include<queue>
#include "Event.h"
#include "GlobalEventList.h"
using namespace std;

GlobalEventList::GlobalEventList()
{
   GEL = priority_queue<Event>(); 
}

void GlobalEventList::addEvent(const Event& passed)
{
    GEL.push(passed);
}

Event GlobalEventList::nextEvent()
{
    Event returned = GEL.top();
    GEL.pop();
    return returned;
}
