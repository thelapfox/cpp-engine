#include "event_system.hpp"

#include <iostream>

using namespace Engine::Core;

struct IntPayload {
    const int x;
    const int y;
};

struct FloatPayload {
    const float d;
};

void func1(std::shared_ptr<Event> event) {
    auto payload = std::static_pointer_cast<IntPayload>(event->GetPayload());
    std::cout << "(" << payload->x << ", " << payload->y << ")" << std::endl;
}

void func2(std::shared_ptr<Event> event) {
    auto payload = std::static_pointer_cast<FloatPayload>(event->GetPayload());
    std::cout << "(" << payload->d << ")" << std::endl;
}

int main() {
    
    EventManager manager = EventManager();

    const std::string event_type_int = "EVENT_TYPE_INT";
    const std::string event_type_float = "EVENT_TYPE_FLOAT";

    {
        std::function<void(std::shared_ptr<Event> ptr)> fp = func1;
        manager.add_listener(event_type_int, func1);
    }

    {
        std::function<void(std::shared_ptr<Event> ptr)> fp = func2;
        manager.add_listener(event_type_float, func2);
    }

    {
        auto int_payload = std::make_shared<IntPayload>(IntPayload{1,2}); 
        auto ev = std::make_shared<Event>(event_type_int, int_payload);

        manager.dispatch_immediately(ev);
    }

    {
        auto float_payload = std::make_shared<FloatPayload>(FloatPayload{6.0f}); 
        auto ev = std::make_shared<Event>(event_type_float, float_payload);

        manager.dispatch_immediately(ev);
    }

    std::function<void(std::shared_ptr<Event> ptr)> fp = func1;
    manager.remove_listener(event_type_int, func1);

    return 0;
}
