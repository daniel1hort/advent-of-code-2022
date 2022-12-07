#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 100

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static void remove_last(char* signal, size_t size) {
	for (int i = 0; i < size - 1; i++) {
		signal[i] = signal[i + 1];
	}
}
static bool is_start_of_packet(char* signal, size_t size) {
	for (int i = 0; i < size - 1; i++) {
		if (strchr(signal + i + 1, signal[i]) != NULL)
			return false;
	}
	return true;
}

static void first(void) {
	FILE* in = open_file("day6.in");

	char signal[5] = { 0 };
	char new_char = 0;
	int position = 4;
	fgets(signal, 5, in);
	while (!is_start_of_packet(signal, 4) && (new_char = fgetc(in)) != EOF) {
		position++;
		remove_last(signal, 4);
		signal[3] = new_char;
	}
	printf_s("%d\n", position);
	fclose(in);
}

static void second(void) {
	FILE* in = open_file("day6.in");

	char signal[15] = { 0 };
	char new_char = 0;
	int position = 14;
	fgets(signal, 15, in);
	while (!is_start_of_packet(signal, 14) && (new_char = fgetc(in)) != EOF) {
		position++;
		remove_last(signal, 14);
		signal[13] = new_char;
	}
	printf_s("%d\n", position);
	fclose(in);
}

static int main(void) {
	first();
	second();
	return 0;
}