#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "level.h"
#include <cstdarg>

namespace simple_log {
    class Message {
    public:
        Message(Level::LoggingLevel lvl, const char * name);
        Message(Level::LoggingLevel lvl, const char * file,
            int line, const char * function);
        char * getMessage();
        bool messageProcessed() const;
        virtual ~Message();
    protected:    
        virtual const char * makeMessage() = 0;
        
        char * _buffer;
        const char *  _lvl;
        const char * _name;
        const char * _file;
        int _line;
        const char * _function;
    };
    
    class SimpleMessage : public Message {
    public:
        SimpleMessage(Level::LoggingLevel lvl, const char * name, 
            const char * msg);
        SimpleMessage(Level::LoggingLevel lvl, const char * file, 
            int line, const char * func, const char * msg);
    private:
        const char * makeMessage();
        const char * _msg;
    };
    
    class FormattedMessage : public Message{
    public:
        FormattedMessage(Level::LoggingLevel lvl, const char * name, 
            const char * fstr, va_list args);
        FormattedMessage(Level::LoggingLevel lvl, const char * file, int line,
            const char * function, const char * fstr, va_list args);
        ~FormattedMessage();
    private:
        const char * makeMessage();
        char * _msgbuf;
        const char * _fstr;
        va_list _args;
    };
}

#endif
