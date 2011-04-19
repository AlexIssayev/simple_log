CXXFLAGS = -g -Wall

OBJS = appender.o level.o logger.o message.o

.PHONY: default sources check clean

default: libsimple_log.a

libsimple_log.a : sources
	ar rs libsimple_log.a $(OBJS)

sources: $(OBJS)

check: message_test logger_test
	@echo testing message
	@unit_tests/message_test || touch errflag
	@echo testing logger
	@unit_tests/logger_test || touch errflag
	@if test -f errflag; then code=1; else=0; fi; \
		$(RM) -f errflag; exit $$code

message_test: libsimple_log.a unit_tests/message_test.cpp
	-cd unit_tests; \
	$(CXX) -g -Wall -I.. -L.. -o $@ message_test.cpp -lsimple_log
	
logger_test: libsimple_log.a unit_tests/logger_test.cpp
	-cd unit_tests; \
	$(CXX) -g -Wall -I.. -L.. -o $@ logger_test.cpp -lsimple_log
	
clean:
	$(RM) *.o
	$(RM) *.log
	-cd unit_tests; $(RM) logger_test message_test
	$(RM) libsimple_log.a
