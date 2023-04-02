#ifndef EVENT_SYSTEM_
#define EVENT_SYSTEM_

#include <string>


namespace Engine::Core {

    class Event {
    public:
        Event(const std::string type, const void* payload)
         : _type(type), _payload(payload) {}

        const std::string& GetType() const { return _type; }
        const void* GetPayload() const { return _payload; }

        bool GetFlag() const { return _flag; }
        void SetFlag(bool flag) { _flag = flag; }

    private:
        const std::string _type;
        const void* _payload;

        bool _flag;
    };

    /*class EventManager {
    
    

    public:

    private:
        std::unordered_map<>
    };*/

}


#endif  // EVENT_SYSTEM_
