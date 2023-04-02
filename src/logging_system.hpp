#ifndef LOGGING_SYSTEM_
#define LOGGING_SYSTEM_

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "event_system.hpp"


using namespace std;

namespace Engine::Core {

    // logging struct carries data
    struct Log  {

        enum Type {
            INFO, WARNING, ERROR
        };

        // logging should carry a type of log and then a string
        const unordered_map<Type, vector<string>> log;
    };

    class LogManager {
    public:
        LogManager(const EventManager& manager) : _manager(manager) {
            string event_type = "LOGGING_EVENT";
            manager.AddListener(event_type, &DebugFunction);
        }

    private:
        int DebugFunction(const Event& logging) {  
            auto* payload = (Log*) logging.GetPayload();

            for(auto& pair : payload->log) {

                auto type = [pair]() -> std::string {
                    switch (pair.first) {
                        case Log::Type::INFO : return "INFO";
                        case Log::Type::WARNING : return "WARNING";
                        case Log::Type::ERROR : return "ERR";

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

        const EventManager& _manager;

    };

};


#endif  // LOGGING_SYSTEM_
