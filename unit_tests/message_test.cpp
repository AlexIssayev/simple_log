#include "message.h"
#include <cstdio>
#include <cstring>

#define ASSERT(expr, msg)  \
if(!(expr)) {              \
    fprintf(stderr, (msg));\
    fprintf(stderr, "\n"); \
    return 1;              \
}

const char * answer = "Simple formatting a number: 42 a string: 42";

Message * makeMessage(const char * fstr, ...) {
    va_list args;
    va_start(args, fstr);
    Message * msg = new Message(fstr, args);
    va_end(args);
    return msg;
}

int main(int argc, char ** argv) {
    const char * fstr1 = "Simple formatting "
        "a number: %d a string: %s";
    Message * msg1 = makeMessage(fstr1, 42, "42");
    char * buf = msg1->getFormattedMessage();
    ASSERT(msg1->messageProcessed(), "Error: Message buffer is empty");
    ASSERT(strcmp(buf, answer) == 0, "Error: Formatting failed");
    printf(buf);
    printf("\n");
    char * buf_p = msg1->getFormattedMessage();
    ASSERT(buf == buf_p, "Error: buffers are different");
    printf("Tests Succesful\n");
    return 0;
}
