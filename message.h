#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <cstdarg>

class Message {
public:
    Message(const char * fstr, va_list args);
    char * getFormattedMessage();
    bool messageProcessed() const;
    ~Message();
private:
    const char * _fstr;
    va_list _args;
    char * _buffer;
};

#endif
