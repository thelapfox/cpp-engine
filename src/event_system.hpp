#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>

 
class Event {
    public:
        Event(const std::string type, const std::shared_ptr<void>& source, const std::shared_ptr<void>& payload)
            : m_type(type), m_source(source), m_payload(payload) {}

        std::string GetType() const { return m_type; }
        std::shared_ptr<void> GetSource() const { return m_source; }
        std::shared_ptr<void> Getpayload() const { return m_payload; }

    private:
        std::string m_type;
        std::shared_ptr<void> m_source; 
        std::shared_ptr<void> m_payload;
};

class EventManager {

    using Listener = std::function<void(const Event&)>;

    public:
        void subscribe_listener(const std::string type, Listener listener) {
            m_listeners[type].push_back(listener);
        }

        void unsubscribe_listener(const std::string type, Listener listener) {
            auto& listeners = m_listeners[type];
            listeners.erase(
                std::remove(listeners.begin(), listeners.end(), listener),
                listeners.end()
            );
        }

        void dispatch(const Event& event) const {
            auto it = m_listeners.find(event.GetType());
            if(it != m_listeners.end()) {
                for(const auto& listener : it-> second) {
                    listener(event);
                }
            }
        }

    private:
        std::unordered_map<const std::string, std::vector<Listener>> m_listeners;
};

#endif  // EVENT_SYSTEM_
