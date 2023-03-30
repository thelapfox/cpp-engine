#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Engine {
    namespace Core {
        class Event {
            public:
                Event(const std::string& type, const std::shared_ptr<void>& source, const std::shared_ptr<void>& payload)
                    : m_type(type), m_source(source), m_payload(payload) {}

                const std::string& GetType() const { return m_type; }
                const std::shared_ptr<void>& GetSource() const { return m_source; }
                const std::shared_ptr<void>& Getpayload() const { return m_payload; }

            private:
                std::string m_type;
                std::shared_ptr<void> m_source; 
                std::shared_ptr<void> m_payload;
        };

        class EventManager {

            using Listener = std::function<void(const Event&)>;

            public:
                void subscribe_listener(const std::string& type, const Listener& listener);

                void unsubscribe_listener(const std::string& type, const Listener& listener);

                void dispatch(const Event& event);

            private:
                std::unordered_map<std::string, std::vector<Listener>> m_listeners;
        };

    }
}


#endif  // EVENT_SYSTEM_
