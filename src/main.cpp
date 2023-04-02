#include "event_system.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace Engine::Core;

struct Collision  {
    const int x;
    const int y;
};

struct Logging  {
    enum Type {
        INFO, WARNING, ERROR
    };

    const std::unordered_map<Type, std::vector<std::string>> log;
};

int func1(Event& collision) {  
    auto payload =  (Collision*) collision.GetPayload();
    std::cout << "(" << payload->x << "," << payload->y << ")" << std::endl;

    return 0;
}

int func2(Event& logging) {  
    auto payload = (Logging*) logging.GetPayload();

    for(auto& pair : payload->log) {

        auto type = [pair]() -> std::string {
            switch (pair.first) {
                case Logging::Type::INFO : return "INFO";
                case Logging::Type::WARNING : return "WARNING";
                case Logging::Type::ERROR : return "ERR";

                default: return "ERR";
            }
        };

        std::string msg = "[" + type() + "]: \n";
        for(auto& log : pair.second) {
            msg += log + "\n";
        }

        std::cout << msg << std::endl;
    }

    return 0;
}

int main() {

    using Listener = int (*)(Event&);
    std::unordered_map<std::string, std::vector<Listener>> listeners;

    {
        std::string event_type = "EVENT_COLLISION";
        listeners[event_type].push_back(&func1);
    }

    {
        std::string event_type = "LOGGING_COLLISION";
        listeners[event_type].push_back(&func2);
    }

    {
        std::string event_type = "EVENT_COLLISION";
        Collision payload = {1, 2};
        Event event = Event(event_type, &payload);
        for(auto& listner : listeners[event_type]) {
            listner(event);
        }
    }

    {
        std::string event_type = "LOGGING_COLLISION";
        std::unordered_map<Logging::Type, std::vector<std::string>> log = {
            {Logging::Type::INFO, {"ONE", "TWO", "THREE"}}
        };
        Logging payload = {log};
        Event event = Event(event_type, &payload);
        for(auto& listner : listeners[event_type]) {
            listner(event);
        }
    }

    return 0;
}
