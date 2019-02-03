CC=g++
CFLAGS=-c -std=c++1z -Wall -Wextra -Wpedantic -Werror
LDFLAGS=
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=course_project

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

package:
	rm -f $(EXECUTABLE).zip
	zip $(EXECUTABLE).zip $(SOURCES) $(HEADERS)
	zip -d  $(EXECUTABLE).zip test_runner.h