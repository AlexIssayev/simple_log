CXXFLAGS = -g -Wall

OBJS = appender.o level.o logger.o message.o

.PHONY: default sources check clean

default: sources

sources: $(OBJS)

check: message_test logger_test
	@echo testing message
	@unit_tests/message_test || touch errflag
	@echo testing logger
	@unit_tests/logger_test || touch errflag
	@if test -f errflag; then code=1; else=0; fi; \
		$(RM) -f errflag; exit $$code

message_test: sources unit_tests/message_test.cpp
	-cd unit_tests; \
	$(CXX) -g -Wall -I.. -o $@ ../message.o ../level.o message_test.cpp
	
logger_test: sources unit_tests/logger_test.cpp
	-cd unit_tests; \
	$(CXX) -g -Wall -I.. -o $@ $(OBJS:%=../%) logger_test.cpp
	
clean:
	$(RM) *.o
	$(RM) *.log
	-cd unit_tests; $(RM) logger_test message_test
