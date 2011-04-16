#include "level.h"

using namespace std;

namespace simple_log {
    const string names[7] = {
        "NONE",
        "FATAL",
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
        "TRACE"
    };
    
    const std::string & Level::LevelName(LoggingLevel lvl) {
        return names[lvl];
    }
