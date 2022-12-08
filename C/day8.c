#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define SIZE 256
#define MAP_SIZE 99

int map[MAP_SIZE][MAP_SIZE];

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static bool is_visible(int line, int col) {
	int height = map[line][col];
check1: for (int i = 0; i < line; i++) if (map[i][col] >= height) goto check2; return true;
check2: for (int i = line + 1; i < MAP_SIZE; i++) if (map[i][col] >= height) goto check3; return true;
check3: for (int i = 0; i < col; i++) if (map[line][i] >= height) goto check4; return true;
check4: for (int i = col + 1; i < MAP_SIZE; i++) if (map[line][i] >= height) return false;
}

static int scenic_score(int line, int col) {
	int score = 1, dist, i;
	for (i = line - 1, dist = 1; i > 0 && map[line][col] > map[i][col]; i--, dist++); score *= dist;
	for (i = line + 1, dist = 1; i < MAP_SIZE - 1 && map[line][col] > map[i][col]; i++, dist++); score *= dist;
	for (i = col - 1, dist = 1; i > 0 && map[line][col] > map[line][i]; i--, dist++); score *= dist;
	for (i = col + 1, dist = 1; i < MAP_SIZE - 1 && map[line][col] > map[line][i]; i++, dist++); score *= dist;
	return score;
}

static setup() {
	FILE* in = open_file("day8.in");
	int line = 0;
	int col = 0;
	char height;

	while ((height = fgetc(in)) != EOF) {
		if (height == "\n") {
			line++;
			col = 0;
		}
		else if (isdigit(height))
			map[line][col++] = height - 48;
	}
	fclose(in);
}

static void first(void) {
	int count = 0;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (is_visible(i, j))
				count++;
		}
	}

	printf_s("%d\n", count);
}

static void second(void) {
	int max_score = 0;
	for (int i = 1; i < MAP_SIZE - 1; i++) {
		for (int j = 1; j < MAP_SIZE - 1; j++) {
			max_score = max(max_score, scenic_score(i, j));
		}
	}

	printf_s("%d\n", max_score);
}

int main(void) {
	setup();
	first();
	second();
	return 0;
}