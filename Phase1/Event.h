#ifndef EVENT_SDA
#define EVENT_SDA

//used to distiguish between events types
enum class EventType {Arrival,Departure,Nothing};

class Event
{
    private:
        //all events have a time and event type 
        //assoiated with them
        double      time;
        EventType   event_type;
    public:
        //we create an event by hiving it its time and 
        //telling it what type of event it will be
        Event(double t,EventType type);
        //used to compare 2 events. This is implemented the way it 
        //is so that i can use a priority queue. 
        //I want event sorted by smallest time to largest so 
        //that is why the operation insde operator< is a >
        bool operator<(const Event& E) const;
        //we want to find out why type of event the 
        //event is
        EventType getEventType() const;
        //we get the time the event occures at
        double getTime() const;
};
#endif 
