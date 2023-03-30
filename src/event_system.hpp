#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

namespace Engine {
    namespace Core {

        class Event {
            public:
                Event(const std::string event_type, std::shared_ptr<void> event_payload)
                : _type(event_type), _payload(event_payload) {}

                std::string GetType() const { return _type; }
                std::shared_ptr<void> GetPayload() const { return _payload; }

            private:
                const std::string _type;
                std::shared_ptr<void> _payload;
        };

        class EventManager {
            using Listener = std::function<void(std::shared_ptr<Event> ptr)>;
            public:
                void add_listener(const std::string event_type, Listener listener);
                void remove_listener(const std::string event_type, Listener listener);

                void dispatch_immediately(const std::shared_ptr<Event> event);

            private:
                std::unordered_map<std::string, std::vector<Listener>> _listeners;
        };

    }
}


#endif  // EVENT_SYSTEM_
