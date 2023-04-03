#ifndef LOGGING_SYSTEM_
#define LOGGING_SYSTEM_

#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

#include <iostream>

#include "event_system.hpp"


using namespace std;
namespace Engine::Core {

struct LogData {
    enum LogType {
        INFO, WARNING, ERROR
    };

    static std::string GetType(LogType logtype) {
        switch (logtype) {
        case LogType::INFO : return "INFO";
        case LogType::WARNING : return "WARNING";
        case LogType::ERROR : return "ERROR";
        
        default: return "ERR";
        }
    }

    static std::string GetTime(const std::string& format) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(
            std::localtime(&now_c),
            format.c_str()
        );

        return ss.str();
    }

    const std::string time;
    const std::pair<LogType, std::string> log;
};

class Debugger : public IObserver {
public:
    void onNotify(const Event& event) override {
        auto payload = std::static_pointer_cast<LogData>(event.GetPayload());

        auto& pair = payload->log;
        std::string msg = "<" +  payload->time + "> [" + payload->GetType(pair.first) + "] " + pair.second;

        std::cout << msg << std::endl;
    }
};

};

#endif  // LOGGING_SYSTEM_
