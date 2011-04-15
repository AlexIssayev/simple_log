CXXFLAGS = -g -Wall

.PHONY: default check clean

default: appender.o

appender.o: appender.cc

check: logger_test
	@./logger_test || exit 1

logger_test: appender.o logger_test.cc
	$(CXX) -g -o $@ appender.o logger_test.cc
	
clean:
	$(RM) *.o
	$(RM) *.log
	$(RM) logger_test