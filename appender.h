#ifndef _APPENDER_H_
#define _APPENDER_H_

#include "message.h"
#include "gen_utils.h"
#include <cstdio>
#include <cstdarg>
#include <vector>

/*
 * Author: Alexander Issayev
 */
 
/* Appender class, provides RAII semantics for writing
 * to log files. The static append method writes to all 
 * open appenders.
 */

namespace simple_log {
    class Appender {
    public:	
        /* Opens file in write or append mode.
         * Throws an exception if file cannot be opened.
         *
         * filename: File to be written to.
         * maxlvl: Highest level of debugging info to append.
         * append: Append to file or overwrite
         */
        Appender(const char * filename, Level::LoggingLevel maxlvl, bool append);
        
        /* Enable writing to cerr with Max Level: maxLvl*/
        static void enableConsole(Level::LoggingLevel maxLvl);
        /* Stop writing to console */
        static void disableConsole();
        
        /* Destroy me and release file handle. */
        ~Appender();
        
        /* Append given message to all active appenders
         * and console if applicable.
         *
         * msg: Message to append.
         * lvl: Level of message to append.
         */
        static void appendAll(Level::LoggingLevel lvl, Message * msg);
    private:
        /* Do not allow copy constructors or assignments */
        DISALLOW_COPY_AND_ASSIGN(Appender);
        /* Write message to my file */
        void append(Level::LoggingLevel lvl, Message * msg);

        int index;
        Level::LoggingLevel maxlvl;
        FILE * logfile;
        const char * filename;
        
        /* Information about console */
        static Level::LoggingLevel consoleLevel;
        static bool writeToConsole;
        
        /* List of all appenders to write to
           List does not own appenders */
        static std::vector<Appender *> appenders;
    };
}
#endif

