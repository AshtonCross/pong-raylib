CXX = gcc
CXXFLAGS = -Wall -Wextra 
RAYLIB = $(shell pkg-config --cflags --libs raylib) # raylib-devel

SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)

pong: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o pong $(RAYLIB)

run: pong
	./pong

clean:
	rm -f pong

.PHONY: run clean  
