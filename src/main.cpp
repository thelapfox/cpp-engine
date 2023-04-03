#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>


enum EventType {
    LOGGING, COLLISION
};

class Event {
public:
    Event(EventType type, std::shared_ptr<void> payload) : _type(type), _payload(payload) {}

    const EventType& GetType() const { return _type; }
    const std::shared_ptr<void> GetPayload() const { return _payload; }

    void SetFlag(bool flag) { _flag = flag; }
    const bool& GetFlag() const { return _flag; }

private:
    const EventType _type;
    const std::shared_ptr<void> _payload;

    bool _flag;
};

class IObserver {
public:
    virtual void onNotify(const Event& event) = 0;
};

class Manager {

    using Observer = std::shared_ptr<IObserver>;

public:
    void Subscribe(EventType type, Observer observer) {
        _subscribers[type].push_back(observer);
    }

    void Unsubscribe(EventType type, Observer observer) {
        if(_subscribers.find(type) == _subscribers.end()) { return; }

        auto& vec = _subscribers[type];
        vec.erase(
            std::remove(vec.begin(), vec.end(), observer),
            vec.end()
        );
    }

    void AddEvent(const Event& event) {
        _events.push_back(event);
    }

    void dispatchImmediately(const Event& event) {
        auto& type = event.GetType();
        if(_subscribers.find(type) == _subscribers.end()) { return; }

        for(auto& pair : _subscribers[type]) {
            pair->onNotify(event);
        }
    }

    void Dispatch() {
        for(auto& event : _events) {

            auto& type = event.GetType();
            if(_subscribers.find(type) == _subscribers.end()) { continue; }

            for(auto& pair : _subscribers[type]) {
                pair->onNotify(event);
            }
        }
    }

private:
    std::vector<Event> _events;
    std::unordered_map<EventType, std::vector<Observer>> _subscribers;
};

struct Payload {
    const int x;
    const int y;
};

class Collider : public IObserver {
public:
    void onNotify(const Event& event) override {
        auto payload = std::static_pointer_cast<Payload>(event.GetPayload());
        std::cout << "(" << payload->x << "," << payload->y << ")" << std::endl;
    }
};

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

int main() {

    Manager manager;

    {
        auto mycollider = std::make_shared<Collider>(Collider());
        manager.Subscribe(EventType::COLLISION, mycollider);
    }

    {
        auto mydebugger = std::make_shared<Debugger>(Debugger());
        manager.Subscribe(EventType::LOGGING, mydebugger);
    }

    {
        auto payload = std::make_shared<Payload>(Payload{1, 2});
        Event event = Event(EventType::COLLISION, payload);
        manager.AddEvent(event);
    }

    {
        std::pair<LogData::LogType, std::string> log = {
            LogData::LogType::INFO, "Something was created."
        };
        std::string time = LogData::GetTime("%Y-%m-%d %H:%M:%S");

        auto payload = std::make_shared<LogData>(LogData{time, log});
        Event event = Event(EventType::LOGGING, payload);
        manager.AddEvent(event);
    }


    manager.Dispatch();

    return 0;
}
