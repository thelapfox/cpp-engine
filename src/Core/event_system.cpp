#include "event_system.hpp"

using namespace Engine::Core;

void EventManager::AddListener(const std::string type, Observer observer) {
    _listeners[type].push_back(observer);
}

void EventManager::AddEvent(Event& event) {
    _events.push_back(event);
}

void EventManager::DispatchImmediately(Event& event) {
    auto& type = event.GetType();
    if(_listeners.find(type) == _listeners.end()) { return; }

    for(auto& listener : _listeners[type]) {
        listener->onNotify(event);
    }

    event.SetFlag(true);
}

void EventManager::DispatchEvents() {
    for(auto& event : _events) {
        if(event.GetFlag()) { return; }

        auto& type = event.GetType();
        if(_listeners.find(type) == _listeners.end()) { return; }

        for(auto& listener : _listeners[type]) {
            listener->onNotify(event);
        }

        event.SetFlag(true);
    }

    _events.erase(
        std::remove_if(
            _events.begin(),
            _events.end(),
            [](const Event& event){ return event.GetFlag(); }
        ),
        _events.end()
    );
}
