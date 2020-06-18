HEADERS = model.hpp view.hpp controller.hpp
SOURCES = main.cpp
CC = g++
CFLAGS = -std=c++11
LDFLAGS = 
EXECUTABLE = snake
LIBS = -lncurses -pthread
RM = rm -rf

all: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS) $(LIBS)

clean:
	$(RM) *.o $(EXECUTABLE)

