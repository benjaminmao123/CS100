CC = g++
CC_FLAGS = -Iinclude -Wall -Werror -ansi -pedantic -std=c++11

TARGET = ./bin/rshell
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES: .cpp=.o)
HEADER = header

all:
	mkdir -p bin
	$(CC) $(CC_FLAGS) $(SOURCES) -o $(TARGET) -I $(HEADER)
	
clean:
	rm -rf ./$(TARGETDIR)