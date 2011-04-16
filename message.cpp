#include "message.h"
#include <cstdio>

static int const BUF_SIZE = 1024;

Message::Message(const char * fstr, va_list args) : 
    _fstr(fstr), _buffer(NULL) {
        va_copy(_args, args);
    }
    
Message::~Message() {
    delete[] _buffer;
    va_end(_args);
    _buffer = NULL;
}

bool Message::messageProcessed() const {
    return _buffer != NULL;
}

char * Message::getFormattedMessage() {
    if (!messageProcessed()) {
        int size = BUF_SIZE;
        do {
            _buffer = new char[size];
            int res = vsprintf(_buffer, _fstr, _args);
            if (res < 0) {
                size *= 2;
                delete[] _buffer;
            } else {
                return _buffer;
            }
        } while (true);
    } else {
        return _buffer;
    }
}
