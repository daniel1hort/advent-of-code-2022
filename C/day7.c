#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define SIZE 100
#define REL_NULL UINT16_MAX
#pragma warning (disable: 6385)
#pragma warning (disable: 6386)

typedef enum {NODE_FILE, NODE_DIRECTOR} node_type_t;
typedef uint16_t relative_ptr_t;
typedef struct {
	relative_ptr_t v[20];
	size_t count;
} list_t;
typedef struct {
	node_type_t type;
	size_t  size;
	list_t children;
	relative_ptr_t parent;
	char name[32];
} node_t;
node_t nodes[1000];
size_t node_count;

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

#define add_node(node) nodes[node_count++] = node
#define add_child(parent, child) nodes[parent].children.v[nodes[parent].children.count++] = child;
static node_t make_director(const char* name, relative_ptr_t parent) {
	node_t node = { 0 };
	node.parent = parent;
	node.type = NODE_DIRECTOR;
	strcpy_s(node.name, 32, name);
	return node;
}
static node_t make_file(const char* name, relative_ptr_t parent, size_t size) {
	node_t node = { 0 };
	node.parent = parent;
	node.type = NODE_FILE;
	node.size = size;
	strcpy_s(node.name, 32, name);
	return node;
}
static relative_ptr_t get_director_ptr(const char* name, relative_ptr_t parent) {
	for (int i = 0; i < node_count; i++)
		if (nodes[i].type == NODE_DIRECTOR
			&& nodes[i].parent == parent
			&& _stricmp(nodes[i].name, name) == 0)
			return i;
	return REL_NULL;
}
static void init_file_system() {
	node_t node = make_director("/", REL_NULL);
	add_node(node);
}

static read_data(FILE* in) {
	relative_ptr_t curr_node_ptr = REL_NULL;
	char buffer[SIZE] = { 0 };
	node_t node = { 0 };

	while (fgets(buffer, SIZE, in)) {
		buffer[strlen(buffer) - 1] = NULL;
		memset(&node, 0, sizeof(node_t));
		if (_strnicmp(buffer, "$ cd ..", 7) == 0) {
			if (nodes[curr_node_ptr].parent != REL_NULL)
				curr_node_ptr = nodes[curr_node_ptr].parent;
		}
		else if (_strnicmp(buffer, "$ cd", 4) == 0) {
			relative_ptr_t dir_ptr = get_director_ptr(buffer + 5, curr_node_ptr);
			curr_node_ptr = dir_ptr;
		}
		else if (_strnicmp(buffer, "$ ls", 4) == 0) {
			continue;
		}
		else if (_strnicmp(buffer, "dir", 3) == 0) {
			node = make_director(buffer + 4, curr_node_ptr);
			add_node(node);
			add_child(curr_node_ptr, node_count - 1);
		}
		else {
			size_t size = 0;
			char* name = NULL;
			name = strchr(buffer, ' ');
			name[0] = NULL;
			size = atoi(buffer);
			node = make_file(name + 1, curr_node_ptr, size);
			add_node(node);
			add_child(curr_node_ptr, node_count - 1);
		}
	}
}

static size_t calculate_director_size(relative_ptr_t node_ptr) {
	node_t* node = &nodes[node_ptr];
	for (int i = 0; i < node->children.count; i++) {
		relative_ptr_t child_ptr = node->children.v[i];
		node_t child = nodes[child_ptr];
		size_t size = 0;
		if (child.type == NODE_FILE)
			size = child.size;
		else if (child.type == NODE_DIRECTOR && child.size == 0)
			size = calculate_director_size(child_ptr);
		else if (child.type == NODE_DIRECTOR && child.size > 0)
			size = child.size;
		node->size += size;
	}
	return node->size;
}
static size_t sum_all_small_directories() {
	size_t sum = 0;
	for (int i = 0; i < node_count; i++)
		if (nodes[i].size <= 100000 && nodes[i].type == NODE_DIRECTOR)
			sum += nodes[i].size;
	return sum;
}

static size_t get_direcory_size_above(size_t size) {
	size_t min_size = SIZE_MAX;
	for (int i = 0; i < node_count; i++)
		if (nodes[i].size >= size && nodes[i].type == NODE_DIRECTOR)
			min_size = min(min_size, nodes[i].size);
	return min_size;
}

static void setup(void) {
	FILE* in = open_file("day7.in");
	init_file_system();
	read_data(in, nodes, &node_count);
	calculate_director_size(0);
	fclose(in);
}

static void first(void) {
	size_t sum = sum_all_small_directories(0);
	printf_s("%llu\n", sum);
}

static void second(void) {
	size_t available_space = 70000000 - nodes[0].size;
	size_t needed_space = 30000000 - available_space;
	size_t folder_to_delete_size = get_direcory_size_above(needed_space);
	printf_s("%llu\n", folder_to_delete_size);
}

static int main(void) {
	setup();
	first();
	second();
	return 0;
}