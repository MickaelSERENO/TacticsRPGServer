rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard, src/, *.cpp)
OBJECTS=$(SRC:.cpp=.o)

CFLAGS := -Iinclude -g
LFLAGS := -lsqlite3 -lcrypto -lpthread -lexpat

all: $(SRC) server

server: $(OBJECTS)
	g++ $(LFLAGS) $^ -o $@

.cpp.o:
	g++ -o $@ -c $< $(CFLAGS)

clean:
	rm $(OBJECTS) server
