#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <string>
#include <memory>

#include <vector>
#include <unordered_map>
#include <algorithm>


namespace Engine::Core {

    // Basic event class 
    //
    class Event {
    private:
        const std::string _type;
        const std::shared_ptr<void> _data;

        bool _handled;

    public:
        Event(const std::string type, const std::shared_ptr<void>& data) : _type(type), _data(data) {}

        const std::string& GetType() const { return _type; }        
        const std::shared_ptr<void>& GetData() const { return _data; }

        const bool& GetFlag() const { return _handled; }
        void SetFlag(bool flag) { _handled = flag; }

    };

    //
    //
    class IObservable {
    public:
        virtual void onNotify(const Event& event) = 0;
    };

    //
    //
    class EventManager {

    using Observer = std::shared_ptr<IObservable>;

    private:
        std::unordered_map<std::string, std::vector<Observer>> _listeners;
        std::vector<Event> _events;

    public:
        void AddListener(const std::string type, Observer observer);

        void AddEvent(Event& event);

        void DispatchImmediately(Event& event);

        void DispatchEvents();

    };

}; // namespace Engine::Core 


#endif  // EVENT_SYSTEM_