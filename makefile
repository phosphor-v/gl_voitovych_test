CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -pthread
SOURCES = main.cpp file_search.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = search.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

