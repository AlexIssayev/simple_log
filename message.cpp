#include "message.h"
#include <stdexcept>
#include <cstdio>
#include <ctime>

namespace simple_log {

    /*Default Buffer size, 1 kb*/
    static const size_t BUF_SIZE = 1024;
    /* How many doubles before we call it a formatting error */
    static const int MAX_REWRITES = 10;
    
    /* Message method definitions */
    
    Message::Message(Level::LoggingLevel lvl, const char * name) 
        : _buffer(NULL), _lvl(Level::LevelName(lvl)), _name(name), 
          _file(NULL), _line(-1), _function(NULL) { }
    
    Message::Message(Level::LoggingLevel lvl, const char * file, int line,
        const char * function) :  _buffer(NULL), _lvl(Level::LevelName(lvl)), 
        _name(NULL), _file(file), _line(line), _function(function) { }
    
    char * Message::getMessage() {
        if (!messageProcessed()) {
            size_t size = BUF_SIZE;
            bool verbose = _name != NULL;
            const char * fstr = verbose ? 
                "%-5s [%02i:%02i:%02i] %s (file %s : line %03d): %s\n" :
                "%-5s %s : %s\n";
            do {
                _buffer = new char[size];
                const char * msg = getMessage();
                int res; 
                if (verbose) { 
                    time_t t = time(NULL);
                    tm * time_info = localtime(&t);
                    res = snprintf(_buffer, size, fstr, _lvl, 
                        time_info->tm_hour, time_info->tm_min, time_info->tm_sec,
                        _function, _file, _line, msg);
                } else {
                    res = snprintf(_buffer, size, fstr, _lvl, _name, msg);
                }
                if (res < 0) {
                    size *= 2;
                    delete[] _buffer;
                } else if (static_cast<size_t>(res) > size) {
                    size = res + 1;
                    delete[] _buffer;
                } else {
                    return _buffer;
                }
            } while (true);
        } else {
            return _buffer;
        }
    }
    
    bool Message::messageProcessed() const {
        return _buffer != NULL;
    }
    
    Message::~Message() {
        delete[] _buffer;
        _buffer = NULL;
    }
    
    /* Simple Message method definitions */
    
    SimpleMessage::SimpleMessage(Level::LoggingLevel lvl, const char * name, 
        const char * msg) : Message(lvl, name), _msg(msg) { }
    
    SimpleMessage::SimpleMessage(Level::LoggingLevel lvl, const char * file, 
        int line, const char * func, const char * msg) 
        : Message(lvl, file, line, func), _msg(msg) { }
        
    const char * SimpleMessage::makeMessage() {
        return _msg;
    }
    
    /* Formatted Message method definitions */
    
    FormattedMessage::FormattedMessage(Level::LoggingLevel lvl, 
        const char * name, const char * fstr, va_list args) 
        : Message(lvl, name), _msgbuf(NULL), _fstr(fstr)
    {
        va_copy(_args, args);
    }
    

    FormattedMessage::FormattedMessage(Level::LoggingLevel lvl, 
        const char * file, int line, const char * function, 
            const char * fstr, va_list args) 
        : Message(lvl, file, line, function), _msgbuf(NULL), _fstr(fstr)
    {
        va_copy(_args, args);
    }
    
    const char * FormattedMessage::makeMessage() {
        if (_msgbuf == NULL) {
            size_t size = BUF_SIZE;
            int safety = 0;
            do {
                _msgbuf = new char[size];
                int res = vsnprintf(_msgbuf, size, _fstr, _args);
                if (res < 0) {
                    size *= 2;
                    ++safety;
                    delete[] _msgbuf;
                } else if (static_cast<size_t>(res) > size) {
                    size = res + 1;
                    delete[] _msgbuf;
                } else {
                    return _msgbuf;
                }
            } while (safety < MAX_REWRITES);
            throw std::runtime_error("Format message longer than "
                "10kbs or has a formatting error.");
        } else {
            return _msgbuf;
        }
    }
    
    FormattedMessage::~FormattedMessage() {
        delete[] _msgbuf;
        va_end(_args);
        _msgbuf = NULL;
    }
}
