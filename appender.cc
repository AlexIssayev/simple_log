#include <ctime>
#include <stdexcept>
#include <string>
#include <cstring>
#include "appender.h"

using namespace std;

 /* String literals representing Level names */

const char * levelNames[] = {"NONE", "ERROR", "WARN", "INFO", "DEBUG"};

/* Helper functions that construct the log message */

int printPreludeFile(FILE * stream, const char * logger, Level lvl);
int printPreludeConsole(FILE * stream, const char * logger, Level lvl);
int printMessage(FILE * stream, const char * msg);
int printFormatMessage(FILE * stream, const char * fstr, va_list args);

/* Appender definitions */

vector<Appender *> Appender::appenders;
Level Appender::consoleLevel = NONE;
bool Appender::writeToConsole = false;

Appender::Appender(const char * filename, Level maxlvl, bool append)
	: maxlvl(maxlvl), filename(filename)
{
	vector<Appender *>::iterator it = Appender::appenders.begin();
	for (; it < Appender::appenders.end(); ++it) {
		int res = strcmp((*it)->filename, filename);
		if (res == 0) {
			throw runtime_error(string("File '") + string(filename) +
				string("' is already open for logging."));
		}
	}
	logfile = fopen(filename, append ? "a" : "w");
	if (!logfile) {
		throw runtime_error(string("Could not open file: ") + 
			string(filename));
	}
	index = Appender::appenders.size();
	Appender::appenders.push_back(this);
}

Appender::~Appender() {
	fclose(logfile);
	logfile = NULL;
	vector<Appender *>::iterator it = Appender::appenders.begin();
	it += index;
	for (vector<Appender *>::iterator p = it; 
			p < Appender::appenders.end(); ++p) {
		--((*p)->index);
	}
	Appender::appenders.erase(it);
}

void Appender::enableConsole(Level maxlvl) {
	Appender::writeToConsole = true;
	Appender::consoleLevel = maxlvl;
}

void Appender::disableConsole() {
	Appender::writeToConsole = false;
}

void Appender::appendAll(const char * logger, Level lvl, 
	const char * msg) 
{
	vector<Appender *>::iterator it = Appender::appenders.begin();
	for(;it < Appender::appenders.end(); ++it) {
		(*it)->append(logger, lvl, msg);
	}
	if (Appender::writeToConsole && lvl <= Appender::consoleLevel) {
		if (printPreludeConsole(stderr, logger, lvl) < 0) {
			throw runtime_error("Writing to stderr failed");
		}
		if (printMessage(stderr, msg) < 0) {
			throw runtime_error("Writing to stderr failed");
		}
	}
}

void Appender::appendFormatAll(const char * logger, Level lvl, 
	const char * fstr, va_list args)
{
	vector<Appender *>::iterator it = Appender::appenders.begin();
	for(;it < Appender::appenders.end(); ++it) {
		(*it)->appendFormat(logger, lvl, fstr, args);
	}
	if (Appender::writeToConsole && lvl <= Appender::consoleLevel) {
		if (printPreludeConsole(stderr, logger, lvl) < 0) {
			throw runtime_error("Writing to stderr failed");
		}
		if (printFormatMessage(stderr, fstr, args) < 0) {
			throw runtime_error("Writing to stderr failed");
		}
	}
}

void Appender::append(const char * logger, Level lvl, 
	const char * msg)
{
	if (lvl <= maxlvl) {
		if (printPreludeFile(logfile, logger, lvl) < 0) {
			throw runtime_error(string("Writing to file '") + 
				string(filename) + string("' failed."));
		}
		if (printMessage(logfile, msg) < 0) {
			throw runtime_error(string("Writing to file '") + 
				string(filename) + string("' failed."));
		}
	}
}

void Appender::appendFormat(const char * logger, Level lvl, 
	const char * fstr, va_list args)
{
	if (lvl <= maxlvl) {
		if (printPreludeFile(logfile, logger, lvl) < 0) {
			throw runtime_error(string("Writing to file '") + 
				string(filename) + string("' failed."));
		}
		if (printFormatMessage(logfile, fstr, args) < 0) {
			throw runtime_error(string("Writing to file '") + 
				string(filename) + string("' failed."));
		}
	}
}

/* Helper function definitions */

int printPreludeFile(FILE * stream, const char * logger, Level lvl) {
	time_t t = time(NULL);
	tm * time_info = localtime(&t);
	return fprintf(stream, "%-5s [%02i:%02i:%02i] %s : ", 
		levelNames[lvl],
		time_info->tm_hour, time_info->tm_min, time_info->tm_sec,
		logger);
}

int printPreludeConsole(FILE * stream, const char * logger, Level lvl) {
	return fprintf(stream, "%-5s %s : ", levelNames[lvl], logger);
}

int printMessage(FILE * stream, const char * msg) {
	int res = fprintf(stream, "%s\n", msg);
	fflush(stream);
	return res;
}

int printFormatMessage(FILE * stream, const char * fstr, va_list args) {
	int res1 = vfprintf(stream, fstr, args);
	int res2 = fprintf(stream, "\n");
	fflush(stream);
	return res1 + res2;
}
