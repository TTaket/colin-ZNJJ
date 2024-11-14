CC = g++
CFLAGS = -Wall -O2
BIN_DIR = bin
SERVER_SIMPLE_DIR = server_simple
CLIENT_SIMPLE_DIR = client_simple
SERVER_WITHPROTOCOL_DIR = server_withprotocol
CLIENT_WITHPROTOCOL_DIR = client_withprotocol

PKG_DIR = pkg
HED_DIR = header
SRC_PKG_FILES = $(shell find $(PKG_DIR) -name '*.cpp')
HED_PKG_FILES = $(shell find $(PKG_DIR) -name '*.h')
HED_HED_FILES = $(shell find $(HED_DIR) -name '*.h')


SRCS_SERVER_SIMPLE = $(shell find $(SERVER_SIMPLE_DIR) -name '*.cpp')
HEDS_SERVER_SIMPLE = $(shell find $(SERVER_SIMPLE_DIR) -name '*.h')

SRCS_CLIENT_SIMPLE = $(shell find $(CLIENT_SIMPLE_DIR) -name '*.cpp')
HEDS_CLIENT_SIMPLE = $(shell find $(CLIENT_SIMPLE_DIR) -name '*.h')

SRCS_SERVER_WITHPROTOCOL = $(shell find $(SERVER_WITHPROTOCOL_DIR) -name '*.cpp')
HEDS_SERVER_WITHPROTOCOL = $(shell find $(SERVER_WITHPROTOCOL_DIR) -name '*.h')

SRCS_CLIENT_WITHPROTOCOL = $(shell find $(CLIENT_WITHPROTOCOL_DIR) -name '*.cpp')
HEDS_CLIENT_WITHPROTOCOL = $(shell find $(CLIENT_WITHPROTOCOL_DIR) -name '*.h')

ALL_FILES = $(SRC_PKG_FILES) $(HED_PKG_FILES) $(HED_HED_FILES)

OBJS = $(SRCS:.cpp=.o)
TARGETS = $(BIN_DIR)/server_simple $(BIN_DIR)/client_simple $(BIN_DIR)/client_withprotocol $(BIN_DIR)/server_withprotocol
INCLUDES = -Iheader -Ipkg/error -Ipkg/net -Ipkg/protocol
all: $(TARGETS)

$(BIN_DIR)/server_simple: $(SRCS_SERVER_SIMPLE) $(HEDS_SERVER_SIMPLE) $(ALL_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_PKG_FILES) $(SRCS_SERVER_SIMPLE) -o $@ 

$(BIN_DIR)/client_simple: $(SRCS_CLIENT_SIMPLE) $(HEDS_CLIENT_SIMPLE) $(ALL_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES)  $(SRC_PKG_FILES) $(SRCS_CLIENT_SIMPLE) -o $@

$(BIN_DIR)/client_withprotocol: $(SRCS_CLIENT_WITHPROTOCOL) $(HEDS_CLIENT_WITHPROTOCOL) $(ALL_FILES) 
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES)  $(SRC_PKG_FILES) $(SRCS_CLIENT_WITHPROTOCOL) -o $@

$(BIN_DIR)/server_withprotocol: $(SRCS_SERVER_WITHPROTOCOL) $(HEDS_SERVER_WITHPROTOCOL) $(ALL_FILES) 
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES)  $(SRC_PKG_FILES) $(SRCS_SERVER_WITHPROTOCOL) -o $@

clean:
	rm -rf $(BIN_DIR) $(OBJS)

.PHONY: all clean