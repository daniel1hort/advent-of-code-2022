#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 100

typedef int range_t[2];

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static inline bool range_fully_contains(range_t a, range_t b) {
	return a[0] <= b[0] && b[1] <= a[1];
}

static inline bool range_overlap(range_t a, range_t b) {
	return a[0] <= b[1] && b[0] <= a[1];
}

static void first(void) {
	FILE* in = open_file("day4.in");

	int count = 0;
	range_t range1, range2;
	while (fscanf_s(in, "%d%*c%d%*c%d%*c%d", range1, range1 + 1, range2, range2 + 1) == 4)
		if (range_fully_contains(range1, range2) || range_fully_contains(range2, range1))
			count++;

	fclose(in);
	printf_s("%d\n", count);
}

static void second(void) {
	FILE* in = open_file("day4.in");

	int count = 0;
	range_t range1, range2;
	while (fscanf_s(in, "%d%*c%d%*c%d%*c%d", range1, range1 + 1, range2, range2 + 1) == 4)
		if (range_overlap(range1, range2))
			count++;

	fclose(in);
	printf_s("%d\n", count);
}

static int main(void) {
	first();
	second();
	return 0;
}