#include "event_system.hpp"
#include "logging_system.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace Engine::Core;

int main() {

    EventManager eventmanager = EventManager();
    LogManager logmanager = LogManager(eventmanager);

    eventmanager.DispatchEvents();

    return 0;
}
