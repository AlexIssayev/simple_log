CXXFLAGS = -g -Wall

.PHONY: default check clean

default: appender.o

appender.o: appender.cpp

check: logger_test
	@./logger_test || exit 1

logger_test: appender.o logger_test.cpp
	$(CXX) -g -o $@ appender.o logger_test.cpp
	
clean:
	$(RM) *.o
	$(RM) *.log
	$(RM) logger_test