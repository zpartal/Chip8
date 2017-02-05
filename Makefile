CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=main.cpp chip8.cpp chip8_tester.cpp chip8_execute.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=chip

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o chip