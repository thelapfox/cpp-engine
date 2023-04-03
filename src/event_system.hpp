#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;
namespace Engine::Core {


class Event {
public:
    Event(const string& type, const std::shared_ptr<void> payload) : _type(type), _payload(payload) {}

    const string& GetType() const { return _type; }
    const std::shared_ptr<void> GetPayload() const { return _payload; }

    void SetFlag(bool flag) { _flag = flag; }
    const bool& GetFlag() const { return _flag; }

private:
    const string _type;
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
    void Subscribe(const string type, Observer observer);

    void Unsubscribe(const string type, Observer observer);

    void AddEvent(const Event& event);

    void DispatchImmediately(const Event& event);

    void Dispatch();

private:
    std::vector<Event> _events;
    std::unordered_map<string, std::vector<Observer>> _subscribers;
};    

};


#endif  // EVENT_SYSTEM_
