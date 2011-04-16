#include "message.h"
#include <cstdio>

static int const BUF_SIZE = 1024;

Message::Message(const char * fstr, va_list args) : 
    fstr(fstr), args(args), buffer(NULL) {}
    
Message::~Message() {
    delete[] buffer;
    buffer = NULL;
}

bool Message::messageProcessed() const {
    return buffer == NULL;
}

char * Message::getFormattedMessage() {
    if (!messageProcessed()) {
        int size = BUF_SIZE;
        do {
            buffer = new char[size];
            int res = vsprintf(buffer, fstr, args);
            if (res < 0) {
                size *= 2;
                delete[] buffer;
            } else {
                return buffer;
            }
        } while (true);
    } else {
        return buffer;
    }
}