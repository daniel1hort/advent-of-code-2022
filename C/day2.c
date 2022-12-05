#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#define and &&
#define is ==

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static int get_score_naive(char their_choice, char my_choice) {
	if (their_choice is 'A' and my_choice is 'X')
		return 1 + 3;
	if (their_choice is 'A' and my_choice is 'Y')
		return 2 + 6;
	if (their_choice is 'A' and my_choice is 'Z')
		return 3 + 0;
	if (their_choice is 'B' and my_choice is 'X')
		return 1 + 0;
	if (their_choice is 'B' and my_choice is 'Y')
		return 2 + 3;
	if (their_choice is 'B' and my_choice is 'Z')
		return 3 + 6;
	if (their_choice is 'C' and my_choice is 'X')
		return 1 + 6;
	if (their_choice is 'C' and my_choice is 'Y')
		return 2 + 0;
	if (their_choice is 'C' and my_choice is 'Z')
		return 3 + 3;
}

static int get_score_correct(char their_choice, char my_choice) {
	if (their_choice is 'A' and my_choice is 'X')
		return 3 + 0;
	if (their_choice is 'A' and my_choice is 'Y')
		return 1 + 3;
	if (their_choice is 'A' and my_choice is 'Z')
		return 2 + 6;
	if (their_choice is 'B' and my_choice is 'X')
		return 1 + 0;
	if (their_choice is 'B' and my_choice is 'Y')
		return 2 + 3;
	if (their_choice is 'B' and my_choice is 'Z')
		return 3 + 6;
	if (their_choice is 'C' and my_choice is 'X')
		return 2 + 0;
	if (their_choice is 'C' and my_choice is 'Y')
		return 3 + 3;
	if (their_choice is 'C' and my_choice is 'Z')
		return 1 + 6;
}

static void first(void) {
	FILE* in = open_file("day2.in");

	int sum = 0;
	char buffer[SIZE] = { 0 };
	char my_choice, their_choice;
	while (fgets(buffer, SIZE, in)) {
		their_choice = buffer[0];
		my_choice = buffer[2];
		sum += get_score_naive(their_choice, my_choice);
	}
	fclose(in);
	printf_s("%d\n", sum);
}

static void second(void) {
	FILE* in = open_file("day2.in");

	int sum = 0;
	char buffer[SIZE] = { 0 };
	char my_choice, their_choice;
	while (fgets(buffer, SIZE, in)) {
		their_choice = buffer[0];
		my_choice = buffer[2];
		sum += get_score_correct(their_choice, my_choice);
	}
	fclose(in);
	printf_s("%d\n", sum);
}

static int main(void) {
	first();
	second();
	return 0;
}