#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SIZE 100

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static int get_priority(char item) {
	if (isupper(item))	return item + 26 - 0x40;
	else				return item - 0x60;
}
static void count_items_in_pouch(const char* pouch, size_t pouch_size, int* count) {
	for (int i = 0; i < pouch_size; i++)
		count[get_priority(pouch[i])]++;
}
static char get_same_priority(int* left_pouch_count, int* right_pouch_count) {
	for (int i = 0; i < SIZE; i++)
		if (left_pouch_count[i] > 0 && right_pouch_count[i] > 0)
			return i;
	return 0;
}
static char get_same_priority3(int count[][SIZE]) {
	for (int i = 0; i < SIZE; i++)
		if (count[0][i] > 0 && count[1][i] > 0 && count[2][i] > 0)
			return i;
	return 0;
}

static void first(void) {
	FILE* in = open_file("day3.in");

	int left_pouch_count[SIZE] = { 0 };
	int right_pouch_count[SIZE] = { 0 };
	char buffer[SIZE] = { 0 };
	int sum = 0;
	while (fgets(buffer, SIZE, in)) {
		size_t pouch_size = strlen(buffer) / 2;
		count_items_in_pouch(buffer, pouch_size, left_pouch_count);
		count_items_in_pouch(buffer + pouch_size, pouch_size, right_pouch_count);
		sum += get_same_priority(left_pouch_count, right_pouch_count);
		memset(left_pouch_count, 0, sizeof(int) * SIZE);
		memset(right_pouch_count, 0, sizeof(int) * SIZE);
	}

	fclose(in);
	printf_s("%d\n", sum);
}

static void second(void) {
	FILE* in = open_file("day3.in");

	int count[3][SIZE] = { 0 };
	char buffer[3][SIZE] = { 0 };
	int sum = 0;
	int line_count = 0;
	while (fgets(buffer[line_count % 3], SIZE, in)) {
		line_count++;
		if (line_count % 3 != 0) continue;

		count_items_in_pouch(buffer[0], strlen(buffer[0]) - 1, count[0]);
		count_items_in_pouch(buffer[1], strlen(buffer[1]) - 1, count[1]);
		count_items_in_pouch(buffer[2], strlen(buffer[2]) - 1, count[2]);
		sum += get_same_priority3(count);
		memset(count, 0, sizeof(int) * SIZE * 3);
	}

	fclose(in);
	printf_s("%d\n", sum);
}

static int main(void) {
	first();
	second();
	return 0;
}