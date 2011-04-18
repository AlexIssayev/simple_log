#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "appender.h"

/* Author: Alexander Issayev
 * 
 * Provides logging functionality. Should be
 * instantiated on a per-class basis.
 */
 
 #define LOG_INFO __FILE__, __LINE__, __func__
 
namespace simple_log {
    class Logger{
    public:
        /* Make logger for a class
         *
         * name: class name
         */
        Logger(const char * name) : name(name) { }
        
        /* Log given message at the given level. 
         *
         * Fatal: Program cannot continue past this point
         * Error: A significant program error.
         * Warn: Possibly an error, but program will function.
         * Info: General status messages.
         * Debug: Debugging level messages.
         * Trace: Very low level trace info
         */
        void Fatal(const char * msg);
        void Error(const char * msg);
        void Warn(const char * msg); 
        void Info(const char * msg);
        void Debug(const char * msg);
        void Trace(const char * msg);
        
        /* Pass additional information by means of macro expansion */
        void Fatal(const char * msg, const char * file, int line, 
            const char * function);
        void Error(const char * msg, const char * file, int line, 
            const char * function);
        void Warn(const char * msg, const char * file, int line, 
            const char * function); 
        void Info(const char * msg, const char * file, int line, 
            const char * function);
        void Debug(const char * msg, const char * file, int line, 
            const char * function);
        void Trace(const char * msg, const char * file, int line, 
            const char * function);
        
        /* As above but with formatting */
        void fFatal(const char * fstr, ...);
        void fError(const char * fstr, ...);
        void fWarn(const char * fstr, ...);
        void fInfo(const char * fstr, ...);
        void fDebug(const char * fstr, ...);
        void fTrace(const char * fstr, ...);
        
        void fFatal(const char * fstr, const char * file, int line, 
            const char * function, ...);
        void fError(const char * fstr, const char * file, int line, 
            const char * function, ...);
        void fWarn(const char * fstr, const char * file, int line, 
            const char * function, ...);
        void fInfo(const char * fstr, const char * file, int line, 
            const char * function, ...);
        void fDebug(const char * fstr, const char * file, int line, 
            const char * function, ...);
        void fTrace(const char * fstr, const char * file, int line, 
            const char * function, ...);
    
    private:
        const char * name;
    };
}
 
#endif
