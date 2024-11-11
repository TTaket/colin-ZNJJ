CC = g++
CFLAGS = -Wall -O2
BIN_DIR = bin
SRC_SERVER = server/server.cpp
SRC_CLIENT = client/client.cpp

SRC_PKG_DIRS = pkg/net pkg/error pkg/protocol
SRCS_PKG = $(foreach dir, $(SRC_PKG_DIRS), $(wildcard $(dir)/*.cpp))
HED_PKG_DIRS = pkg/net pkg/error pkg/protocol header
HEDS_PKG = $(foreach dir, $(HED_PKG_DIRS), $(wildcard $(dir)/*.h))

OBJS = $(SRCS:.cpp=.o)
TARGETS = $(BIN_DIR)/server $(BIN_DIR)/client
INCLUDES = -Ibase -Ipkg/error -Ipkg/net -Ipkg/protocol

all: $(TARGETS)

$(BIN_DIR)/server: $(SRC_SERVER) $(SRCS_PKG) $(HEDS_PKG)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_SERVER) $(SRCS_PKG) -o $@ 

$(BIN_DIR)/client: $(SRC_CLIENT) $(SRCS_PKG) $(HEDS_PKG)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES)  $(SRC_CLIENT) $(SRCS_PKG) -o $@

clean:
	rm -rf $(BIN_DIR) $(OBJS)

.PHONY: all clean