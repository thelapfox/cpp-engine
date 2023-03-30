#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>


class Event {
    public:
        Event(const std::string event_type, void* payload)
         : m_event_type(event_type), m_payload(payload) {}

        std::string GetType() const { return m_event_type; }
        void* GetPayload() const { return m_payload; }

    private:
        const std::string m_event_type;
        void* m_payload;
};

class EventManager {
    public:
        void add_listener(const std::string event_type, void (*listener)(Event*)) {
            m_listeners[event_type].push_back(listener);
        }

        void remove_listener(const std::string event_type, void (*listener)(Event*)) {
            if (m_listeners.find(event_type) != m_listeners.end()) {
                auto& vec = m_listeners[event_type];
                for (auto it = vec.begin(); it != vec.end(); ++it) {
                    if (*it == listener) {
                        vec.erase(it);

                        if(vec.empty()) {
                            m_listeners.erase(event_type);
                        }

                        break;
                    }
                }
            }
        }

        void dispatch_event_immediately(Event* event) {
            const std::string type = event->GetType();
            if (m_listeners.find(type) != m_listeners.end()) {
                for (auto listener : m_listeners[type]) {
                    listener(event);
                }
            }
        }

    private:
        std::unordered_map<std::string, std::vector<void (*)(Event*)>> m_listeners;
};

struct DebugOne {
    const int x;
    const int y;
};

struct DebugTwo {
    const float f;
};

void func1(Event* event) {
    const std::string type = event->GetType();
    DebugOne* payload = static_cast<DebugOne*>(event->GetPayload());
    std::cout << "Function one: " << type << " payload: " << payload->x << ", " << payload->y << std::endl;
}

void func2(Event* event) {
    const std::string type = event->GetType();
    DebugTwo* payload = static_cast<DebugTwo*>(event->GetPayload());
    std::cout << "Function two: " << type << " payload: " << payload->f << std::endl;
}

int main() {

    EventManager event_manager = EventManager();

    DebugOne s1 {1, 2};
    DebugTwo s2 {5.0f};

    const std::string event_type_one = "DEBUG_EVENT_ONE";
    const std::string event_type_two = "DEBUG_EVENT_TWO";

    Event event_one {event_type_one, &s1};
    Event event_two {event_type_two, &s2};

    event_manager.add_listener(event_type_one, &func1);
    event_manager.add_listener(event_type_two, &func2);

    event_manager.dispatch_event_immediately(&event_one);
    event_manager.dispatch_event_immediately(&event_two);

    return 0;
}
