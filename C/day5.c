#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 100
#define STACKS_COUNT 9

typedef struct {
	char v[SIZE];
	size_t size;
} stack_t;

typedef union {
	int v[3];
	struct {
		int move;
		int from;
		int into;
	} m;
} instruction_t;

static inline void stack_add(stack_t* stack, char value) {
	stack->v[stack->size++] = value;
}
static inline char stack_pop(stack_t* stack) {
	if (stack->size == 0) return NULL;
	return stack->v[--(stack->size)];
}
static stack_move_n(stack_t* from, stack_t* to, size_t count) {
	int begin = max(from->size - count, 0);
	for (int i = begin; i < from->size; i++) {
		stack_add(to, from->v[i]);
	}
	from->size = max(from->size - count, 0);
}

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static void read_initial_stacks(FILE* in, stack_t stacks[], int count) {
	const int depth = 8; //taken from input to avoid relocating the values;
	char buffer[SIZE] = { 0 };
	for (int i = depth - 1; i >= 0; i--) {
		fgets(buffer, SIZE, in);
		for (int j = 0; j < count; j++) {
			char value = buffer[4 * j + 1];
			if (isalpha(value)) {
				stacks[j].size++;
				stacks[j].v[i] = value;
			}
		}
	}
	fgets(buffer, SIZE, in);
	fgets(buffer, SIZE, in);
}

static void first(void) {
	FILE* in = open_file("day5.in");
	stack_t stacks[STACKS_COUNT] = { 0 };
	instruction_t ins;
	read_initial_stacks(in, stacks, STACKS_COUNT);
	while (fscanf_s(in, "%*5s %d %*5s %d %*3s %d", ins.v, ins.v + 1, ins.v + 2) == 3) {
		for (int i = 0; i < ins.m.move; i++) {
			char crate = stack_pop(&stacks[ins.m.from - 1]);
			stack_add(&stacks[ins.m.into - 1], crate);
		}
	}

	for (int i = 0; i < STACKS_COUNT; i++) {
		printf_s("%c", stacks[i].v[stacks[i].size - 1]);
	}
	printf_s("\n");
	fclose(in);
}

static void second(void) {
	FILE* in = open_file("day5.in");
	stack_t stacks[STACKS_COUNT] = { 0 };
	instruction_t ins = { 0 };
	read_initial_stacks(in, stacks, STACKS_COUNT);
	while (fscanf_s(in, "%*5s %d %*5s %d %*3s %d", ins.v, ins.v + 1, ins.v + 2) == 3) {
		stack_move_n(&stacks[ins.m.from - 1], &stacks[ins.m.into - 1], ins.m.move);
	}

	for (int i = 0; i < STACKS_COUNT; i++) {
		printf_s("%c", stacks[i].v[stacks[i].size - 1]);
	}
	printf_s("\n");
	fclose(in);
}

static int main(void) {
	first();
	second();
	return 0;
}