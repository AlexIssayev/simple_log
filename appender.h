#ifndef _APPENDER_H_
#define _APPENDER_H_

#include "gen_utils.h"
#include <cstdio>
#include <cstdarg>
#include <vector>

/*
 * Author: Alexander Issayev
 */

/*
 * Level of debug info
 */
enum Level { NONE, ERROR, WARN, INFO, DEBUG };
 
/* Appender class, provides RAII semantics for writing
 * to log files. The static append method writes to all 
 * open appenders.
 */
 
class Appender {
public:	
	/* Opens file in write or append mode.
	 * Throws an exception if file cannot be opened.
	 *
	 * filename: File to be written to.
	 * maxlvl: Highest level of debugging info to append.
	 * append: Append to file or overwrite
	 */
	Appender(const char * filename, Level maxlvl, bool append);
	
	/* Enable writing to cerr with Max Level: maxLvl*/
	static void enableConsole(Level maxLvl);
	/* Stop writing to console */
	static void disableConsole();
	
	/* Destroy me and release file handle. */
	~Appender();
	
	/* Append given message to all active appenders
	 * and console if applicable.
	 *
	 * logger: Name of logger that called append.
	 * msg: Message to append.
	 * lvl: Level of message to append.
	 */
	static void appendAll(const char * logger, Level lvl, 
	      const char * msg);
	
	/* Append given message to all active appenders
	 * Format arguments first.
	 *
	 * logger: Name of logger that called append.
	 * fstr: Format string of message to append.
	 * lvl: Level of message to append.
	 * args: list of arguments to format string
	 */
	static void appendFormatAll(const char * logger, Level lvl, 
		const char * fstr, va_list args);
private:
	/* Do not allow copy constructors or assignments */
	DISALLOW_COPY_AND_ASSIGN(Appender);
	/* Write message to my file */
	void append(const char * logger, Level lvl, const char * msg);
	void appendFormat(const char * logger, Level lvl, 
		const char * fstr, va_list args);

	int index;
	Level maxlvl;
	FILE * logfile;
	const char * filename;
	
	/* Information about console */
	static Level consoleLevel;
	static bool writeToConsole;
	
	/* List of all appenders to write to
	   List does not own appenders */
	static std::vector<Appender *> appenders;
};

#endif

