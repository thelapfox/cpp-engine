#include "event_system.hpp"

using namespace Engine::Core;

void Manager::Subscribe(const string type, Observer observer) {
    _subscribers[type].push_back(observer);
}

void Manager::Unsubscribe(const string type, Observer observer) {
    if(_subscribers.find(type) == _subscribers.end()) { return; }

    auto& vec = _subscribers[type];
    vec.erase(
        std::remove(vec.begin(), vec.end(), observer),
        vec.end()
    );
}

void Manager::AddEvent(const Event& event) {
    _events.push_back(event);
}

void Manager::DispatchImmediately(const Event& event) {
    auto& type = event.GetType();
    if(_subscribers.find(type) == _subscribers.end()) { return; }

    for(auto& pair : _subscribers[type]) {
        pair->onNotify(event);
    }

    //event.SetFlag(true);
}

void Manager::Dispatch() {
    for(auto& event : _events) {
        if(event.GetFlag()) { continue; }

        auto& type = event.GetType();
        if(_subscribers.find(type) == _subscribers.end()) { continue; }

        for(auto& pair : _subscribers[type]) {
            pair->onNotify(event);
        }

        //event.SetFlag(true);
    }

    _events.erase(
        std::remove_if(_events.begin(), _events.end(),
            [](const Event& event){ return event.GetFlag(); }
        ),
        _events.end()
    );
}
