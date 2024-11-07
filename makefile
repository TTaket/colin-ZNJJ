CC = g++
CFLAGS = -Wall -O2
BIN_DIR = bin
SRC_DIRS = server client
SRCS = $(wildcard server/*.cpp) $(wildcard client/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(BIN_DIR)/server $(BIN_DIR)/client
INCLUDES = -Ibase

all: $(TARGETS)

$(BIN_DIR)/server: server/server.cpp $(wildcard base/*.h)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(BIN_DIR)/client: client/client.cpp $(wildcard base/*.h)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf $(BIN_DIR) $(OBJS)

.PHONY: all clean