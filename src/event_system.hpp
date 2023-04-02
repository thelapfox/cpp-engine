#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

namespace Engine::Core {

    class Event {
    public:
        Event(const string type, const void* payload)
         : _type(type), _payload(payload) {}

        const string& GetType() const { return _type; }
        const void* GetPayload() const { return _payload; }

        bool GetFlag() const { return _flag; }
        void SetFlag(bool flag) { _flag = flag; }

    private:
        const string _type;
        const void* _payload;

        bool _flag;
    };

    class EventManager {
    
        using Listener = int (*)(const Event&);

    public:
        void AddListener(const string type, Listener listener) {
            listeners[type].push_back(listener);
        }

        void AddEvent(const Event& event) {
            events.push_back(event);
        }

        void DispatchImmediately(const Event& event) {
            // skip if there is no listeners for an event
            auto& type = event.GetType();
            if(listeners.find(type) == listeners.end()) { return; }

            // call functions
            for(auto& listener : listeners[type]) {
                listener(event);
            }
        }

        void DispatchEvents() {
            for(auto& event : events) {

                // skip if there is no listeners for an event
                auto& type = event.GetType();
                if(listeners.find(type) == listeners.end()) { continue; }

                DispatchImmediately(event);
            }
        }

    private:
        vector<Event> events;
        unordered_map<string, vector<Listener>> listeners;
    };

}


#endif  // EVENT_SYSTEM_
