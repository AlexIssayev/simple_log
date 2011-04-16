#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>

/* Author: Alexnader Issayev
 * 
 * Logging Levels available
 */

namespace simple_log {
    class Level {
        /*
         * Level of debug info
         */
        enum  LoggingLevel { NONE, FATAL, ERROR, WARN, INFO, DEBUG, TRACE };
        
        static const std::string & LevelName(LoggingLevel lvl);
    };
}
 
#endif
