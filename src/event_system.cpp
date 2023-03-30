#include "event_system.hpp"

using namespace Engine::Core;

void EventManager::subscribe_listener(const std::string& type, const Listener& listener) {
    EventManager::m_listeners[type].push_back(listener);   
}
/*
void EventManager::unsubscribe_listener(const std::string& type, const Listener& listener) {
    auto& listeners = EventManager::m_listeners[type];
    for(auto it = listeners.begin(); it != listeners.end(); ++it) {
        if(*it == listener) {
            listeners.erase(it);
            break;
        }
    }

}
*/
void EventManager::dispatch(const Event& event) {
    auto& listeners = EventManager::m_listeners[event.GetType()];
    for(const auto& listener : listeners) {
        listener(event);
    }
}

