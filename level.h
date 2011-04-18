#ifndef _LEVEL_H_
#define _LEVEL_H_

/* Author: Alexnader Issayev
 * 
 * Logging Levels available
 */

namespace simple_log {
    struct Level {
        /*
         * Level of debug info
         */
        enum  LoggingLevel { NONE, FATAL, ERROR, WARN, INFO, DEBUG, TRACE };
        
        static const char * LevelName(LoggingLevel lvl);
    };
}
 
#endif
