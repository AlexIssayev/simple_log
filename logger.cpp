#include "logger.h"

#define LoggingMessages(f_name, level)                                \
                                                                      \
void Logger::f_name(const char * message) {                           \
    Message * msg = new SimpleMessage(Level::level, name, message);   \
    Appender::appendAll(msg, Level::level);                           \
    delete msg;                                                       \
}                                                                     \
                                                                      \
void Logger::f_name(const char * message, const char * file, int line,\
    const char * function) {                                          \
    Message * msg = new SimpleMessage(Level::level, file, line,       \
    function, message);                                               \
    Appender::appendAll(msg, Level::level);                           \
    delete msg;                                                       \
}                                                                     \
                                                                      \
void Logger::f ## f_name(const char * fstr, ...) {                    \
    va_list args;                                                     \
    va_start(args, fstr);                                             \
        Message * msg = new FormattedMessage(Level::level,            \
            name, fstr, args);                                        \
        Appender::appendAll(msg, Level::level);                       \
        delete msg;                                                   \
    va_end(args);                                                     \
}                                                                     \
                                                                      \
void Logger::f ## f_name(const char * fstr, const char * file,        \
    int line, const char * function, ...) {                           \
    va_list args;                                                     \
    va_start(args, function);                                         \
        Message * msg = new FormattedMessage(Level::level,            \
            file, line, function, fstr, args);                        \
        Appender::appendAll(msg, Level::level);                       \
        delete msg;                                                   \
    va_end(args);                                                     \
}

namespace simple_log {
    LoggingMessages(Fatal, FATAL);
    LoggingMessages(Error, ERROR);
    LoggingMessages(Warn, WARN);
    LoggingMessages(Info, INFO);
    LoggingMessages(Debug, DEBUG);
    LoggingMessages(Trace, TRACE);
}