//#include <lua/lua.hpp>
#include "event_system.hpp"
#include "logging_system.hpp"

using namespace std;
using namespace Engine::Core;

int main() {

    /*
    // Create a new Lua state object
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Load and execute a Lua script from a file
    if(luaL_loadfile(L, "../scripts/main.lua") || lua_pcall(L, 0, 0, 0)) {
        // Print an error message if the script fails to load or execute
        const char* errorMessage = lua_tostring(L, -1);
        printf("Error loading script: %s\n", errorMessage);
    }

    // Close the Lua state object and free any resources
    lua_close(L);
    */

   Manager manager;

    const string loggingEvent = "LOGGING_EVENT";

    {
        auto mydebugger = std::make_shared<Debugger>(Debugger());
        manager.Subscribe(loggingEvent, mydebugger);

        std::pair<LogData::LogType, std::string> log = {
            LogData::LogType::INFO, "Something was created."
        };
        std::string time = LogData::GetTime("%Y-%m-%d %H:%M:%S");

        auto payload = std::make_shared<LogData>(LogData{time, log});
        Event event = Event(loggingEvent, payload);
        manager.AddEvent(event);
    }

    manager.Dispatch();

    return 0;
}
