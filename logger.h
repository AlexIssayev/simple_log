#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "appender.h"

/* Author: Alexnader Issayev
 * 
 * Provides logging functionality. Should be
 * instantiated on a per-class basis.
 */
class Logger{
public:
	/* Make logger for a class
	 *
	 * name: class name
	 */
	Logger(const char * name) : name(name) { }
	
	/* Log given message at the given level. 
	 *
	 * Error: A significant program error.
	 * Warn: Possibly an error, but program will function.
	 * Info: General status messages.
	 * Debug: Debugging level messages.
	 */
	void Error(const char * msg) { 
		Appender::appendAll(name, ERROR, msg); 
	}
	void Warn(const char * msg) { 
		Appender::appendAll(name, WARN, msg); 
	}
	void Info(const char * msg) { 
		Appender::appendAll(name, INFO, msg); 
	}
	void Debug(const char * msg) { 
		Appender::appendAll(name, DEBUG, msg); 
	}
	
	/* As above but with formatting */
	void fError(const char * fstr, ...) {
		va_list args;
		va_start(args, fstr);
			Appender::appendFormatAll(name, ERROR, fstr, args);
		va_end(args);
	}
	void fWarn(const char * fstr, ...) {
		va_list args;
		va_start(args, fstr);
			Appender::appendFormatAll(name, WARN, fstr, args);
		va_end(args);
	}
	void fInfo(const char * fstr, ...) {
		va_list args;
		va_start(args, fstr);
			Appender::appendFormatAll(name, INFO, fstr, args);
		va_end(args);
	}
	void fDebug(const char * fstr, ...) {
		va_list args;
		va_start(args, fstr);
			Appender::appendFormatAll(name, DEBUG, fstr, args);
		va_end(args);
	}
private:
	const char * name;
};
 
 
#endif
