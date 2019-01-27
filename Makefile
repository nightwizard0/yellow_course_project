CC=g++
CFLAGS=-std=c++1z -Wall -Wextra -Wpedantic -Werror
LDFLAGS=
SOURCES=main.cpp token.cpp condition_parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=course_project

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)