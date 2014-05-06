#ifndef GLOBAL_EVENT_LIST_SDA
#define GLOBAL_EVENT_LIST_SDA

#include<queue>
using namespace std;

class GlobalEventList
{
    private:
        //we require only inserting and removing elements form our data 
        //structure. We also require that the element that is removed is 
        //the event with the smallest time. Because of this i chose 
        //a priority queue of events keyed to time. By definition a priority
        //queue implements our requirements
        priority_queue<Event> GEL;
    public:
        //we make the GEL an empty priority queue
        GlobalEventList();
        //we add an event to the GEL
        void addEvent(const Event&);
        //we get the next event and we also remove 
        //the top element of the priority queue
        Event nextEvent();
};
#endif
