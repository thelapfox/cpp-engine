#include "event_system.hpp"

using namespace Engine::Core;

void EventManager::add_listener(const std::string event_type, Listener listener) {
    _listeners[event_type].push_back(listener);
}

void EventManager::remove_listener(const std::string event_type, Listener listener) {
    if(_listeners.find(event_type) != _listeners.end()) {
        auto& vec = _listeners[event_type];
        for(auto it = vec.begin(); it != vec.end(); ++it) {
            
            if(*it == listener) {
                vec.erase(it);
            }

            if(vec.empty()) {
                _listeners.erase(event_type);
            }

            break;
        } 
    }
}

void EventManager::dispatch_immediately(const std::shared_ptr<Event> event) {
    const std::string type = event->GetType();
    if(_listeners.find(type) != _listeners.end()) {
        for(auto listener : _listeners[type]) {
            listener(event);
        }
    }
}
