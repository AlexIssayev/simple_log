#include <stdexcept>
#include <string>
#include <cstring>
#include "message.h"
#include "appender.h"

using namespace std;

namespace simple_log {

    /* Appender definitions */

    vector<Appender *> Appender::appenders;
    Level::LoggingLevel Appender::consoleLevel = Level::NONE;
    bool Appender::writeToConsole = false;

    Appender::Appender(const char * filename, Level::LoggingLevel maxlvl, 
        bool append) : maxlvl(maxlvl), filename(filename)
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

    void Appender::enableConsole(Level::LoggingLevel maxlvl) {
        Appender::writeToConsole = true;
        Appender::consoleLevel = maxlvl;
    }

    void Appender::disableConsole() {
        Appender::writeToConsole = false;
    }

    void Appender::appendAll(Level::LoggingLevel lvl, Message * msg) {
        vector<Appender *>::iterator it = Appender::appenders.begin();
        for(;it < Appender::appenders.end(); ++it) {
            (*it)->append(lvl, msg);
        }
        if (Appender::writeToConsole && lvl <= Appender::consoleLevel) {
            int res = fprintf(stderr, "%s", msg->getMessage());
            if (res < 0) { 
                throw runtime_error("Writing to stderr failed");
            }
        }
    }

    void Appender::append(Level::LoggingLevel lvl, Message * msg) {
        if (lvl <= maxlvl) {
            int res = fprintf(logfile, "%s", msg->getMessage());
            if (res < 0) {
                throw runtime_error(string("Writing to file '") + 
                    string(filename) + string("' failed."));
            }
        }
    }
}
