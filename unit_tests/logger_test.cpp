#include "logger.h"
#include "level.h"

#include <iostream>

using namespace std;
using namespace simple_log;

Logger logger1("Logger1");
Logger logger2("Logger2");
Logger fLogger("foo");

void foo() {
	Appender fooApp("foo.log", Level::INFO, true);
	fLogger.Info("I'm in foo");
}

int main(int argc, char ** argv) {
	try {
		Appender errApp("Error.log", Level::ERROR, false);
		Appender debugApp("Debug.log", Level::DEBUG, true);
		Appender * dynApp = new Appender("Dynamic.log", Level::INFO, false);
		try {
			Appender badApp("Error.log", Level::ERROR, false);
		} catch ( exception & e ) {
			cout << "Correctly failed to open two appenders to one file." << endl;
		}
		logger1.Error("This should show up for all Appenders");
		delete dynApp;
		logger1.Error("This should only be in Error and Debug");
		logger2.Info("This should only be in debug");
		Appender::enableConsole(Level::INFO);
		logger1.Info("This should show up on the console.");
		logger2.Debug("This should only be in the debug log");
		fLogger.Info("Entering Foo");
		foo();
		fLogger.Info("Exiting foo.");
		Appender::enableConsole(Level::DEBUG);
		logger2.Debug("This will be in the console.");
		logger1.fDebug("%s - %i", "format test", 42);
		Appender::disableConsole();
		logger2.Debug("This will not be on the console.");
		logger1.Error("Exiting");
	} catch ( exception & e ) {
		cerr << "Unhandled exception: ";
		cerr << e.what() << endl;
		cerr << "Exiting." << endl;
		return 1;
	}
	return 0;
}
