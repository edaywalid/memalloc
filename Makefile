CC = gcc
CFLAGS = -Wall -Wextra -g
OUT_DIR = out
DEBUG_DIR = debug
SRC_DIR = .
EXAMPLES_DIR = examples
TESTS_DIR = tests

MEMALLOC_SRC = $(SRC_DIR)/memalloc.c
MEMALLOC_OBJ = $(OUT_DIR)/memalloc.o

LINKED_LIST_SRC = $(EXAMPLES_DIR)/linked_list.c
BINARY_TREE_SRC = $(EXAMPLES_DIR)/binary_tree.c
DIRECTED_GRAPH_SRC = $(EXAMPLES_DIR)/directed_graph.c

TEST_MEMALLOC_SRC = $(TESTS_DIR)/test_memalloc.c

LINKED_LIST_BIN = $(DEBUG_DIR)/linked_list
BINARY_TREE_BIN = $(DEBUG_DIR)/binary_tree
DIRECTED_GRAPH_BIN = $(DEBUG_DIR)/directed_graph
TEST_MEMALLOC_BIN = $(DEBUG_DIR)/test_memalloc

all: $(MEMALLOC_OBJ) linked_list binary_tree directed_graph

$(MEMALLOC_OBJ): $(MEMALLOC_SRC)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

linked_list: $(MEMALLOC_OBJ)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(MEMALLOC_OBJ) $(LINKED_LIST_SRC) -o $(LINKED_LIST_BIN)
	@echo "Linked List example compiled successfully."

binary_tree: $(MEMALLOC_OBJ)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(MEMALLOC_OBJ) $(BINARY_TREE_SRC) -o $(BINARY_TREE_BIN)
	@echo "Binary Tree example compiled successfully."

directed_graph: $(MEMALLOC_OBJ)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(MEMALLOC_OBJ) $(DIRECTED_GRAPH_SRC) -o $(DIRECTED_GRAPH_BIN)
	@echo "Directed Graph example compiled successfully."

test_memalloc: $(MEMALLOC_OBJ)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(MEMALLOC_OBJ) $(TEST_MEMALLOC_SRC) -o $(TEST_MEMALLOC_BIN)
	@echo "Unit tests compiled successfully."
	@./$(TEST_MEMALLOC_BIN)

clean:
	@rm -rf $(OUT_DIR) $(DEBUG_DIR)
	@echo "Cleaned up build artifacts."

.PHONY: all linked_list binary_tree directed_graph test_memalloc clean

