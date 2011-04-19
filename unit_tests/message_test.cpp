#include "message.h"
#include <cstdio>
#include <cstring>
#include <algorithm>

#define ASSERT(expr, msg)  \
if(!(expr)) {              \
    fprintf(stderr, (msg));\
    fprintf(stderr, "\n"); \
    return 1;              \
}

using namespace simple_log;

const char * answer = "Simple formatting a number 42 a string 42\n";

Message * makeFormattedMessage(const char * fstr, ...) {
    va_list args;
    va_start(args, fstr);
    Message * msg = new FormattedMessage(Level::INFO, "test", fstr, args);
    va_end(args);
    return msg;
}

Message * makeSimpleMessage(const char * message) {
    Message * msg = new SimpleMessage(Level::TRACE, "test", message);
    return msg;
}

Message * makeVerboseSimpleMessage(const char * message) {
    Message * msg = new SimpleMessage(Level::DEBUG, "file", 42, 
        "function", message);
    return msg;
}

int main(int argc, char ** argv) {
    const char * fstr1 = "Simple formatting "
        "a number %d a string %s";
    Message * msg1 = makeFormattedMessage(fstr1, 42, "42");
    char * buf = msg1->getMessage();
    ASSERT(msg1->messageProcessed(), "Error: Message buffer is empty");
    char * msg_end = buf + strlen(buf);
    const char * ptrn = ":";
    char * fmt_msg = std::find_end(buf, msg_end, ptrn, ptrn + 1);
    ASSERT(fmt_msg != msg_end, "Error: No colon found");
    ASSERT(strcmp(fmt_msg + 2, answer) == 0, "Error: Formatting failed");
    printf(buf);
    char * buf_p = msg1->getMessage();
    ASSERT(buf == buf_p, "Error: buffers are different");
    
    const char * reg_str = "Just a regular string";
    Message * msg2 = makeSimpleMessage(reg_str);
    buf = msg2->getMessage();
    ASSERT(msg2->messageProcessed(), "Error: Message buffer is empty");
    msg_end = buf + strlen(buf);
    fmt_msg = std::find_end(buf, msg_end, ptrn, ptrn + 1);
    ASSERT(strncmp(fmt_msg + 2, reg_str, strlen(reg_str)) == 0, 
        "Error: Formatting failed");
    printf(buf);
    buf_p = msg2->getMessage();
    ASSERT(buf == buf_p, "Error: buffers are different");
    
    const char * v_msg = "Verbose message";
    Message * msg3 = makeVerboseSimpleMessage(v_msg);
    buf = msg3->getMessage();
    ASSERT(msg3->messageProcessed(), "Error: Message buffer is empty");
    msg_end = buf + strlen(buf);
    fmt_msg = std::find_end(buf, msg_end, ptrn, ptrn + 1);
    ASSERT(strncmp(fmt_msg + 2, v_msg, strlen(v_msg)) == 0, 
        "Error: Formatting failed");
    printf(buf);
    buf_p = msg3->getMessage();
    ASSERT(buf == buf_p, "Error: buffers are different");
    
    printf("Tests Succesful\n");
    return 0;
}
