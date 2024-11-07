CC = g++
CFLAGS = -Wall -O2
BIN_DIR = bin
SRC_DIRS = server client
SRCS_PKG = $(wildcard pkg/net/*.cpp) $(wildcard pkg/error/*.cpp)
SRC_SERVER = server/server.cpp
SRC_CLIENT = server/client.cpp
SRCS = $(wildcard server/*.cpp) $(wildcard client/*.cpp) $(SRCS_PKG)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(BIN_DIR)/server $(BIN_DIR)/client
INCLUDES = -Ibase -Ipkg/error -Ipkg/net

all: $(TARGETS)
$(BIN_DIR)/server: server/server.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(SRCS_PKG)

$(BIN_DIR)/client: client/client.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(SRCS_PKG)

clean:
	rm -rf $(BIN_DIR) $(OBJS)

.PHONY: all clean