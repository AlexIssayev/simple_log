#include "level.h"

using namespace std;

namespace simple_log {
    const char * names[7] = {
        "NONE",
        "FATAL",
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
        "TRACE"
    };
    
    const char * Level::LevelName(LoggingLevel lvl) {
        return names[lvl];
    }
}
