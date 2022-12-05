#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 256

static FILE* open_file(const char* file_name) {
	FILE* in = NULL;
	if (fopen_s(&in, file_name, "r") != 0) {
		printf_s("Error in opening file");
		exit(errno);
	}
	return in;
}

static void first(void) {
	FILE* in = open_file("day1.in");

	int sum = 0;
	int max_sum = 0;
	char buffer[SIZE];
	while (fgets(buffer, SIZE, in)) {
		if (buffer[0] == '\n') {
			max_sum = max(sum, max_sum);
			sum = 0;
		}
		else {
			buffer[strlen(buffer) - 1] = 0;
			int value = atoi(buffer);
			sum += value;
		}
	}
	fclose(in);
	printf_s("%d\n", max_sum);
}

static void second(void) {
	FILE* in = open_file("day1.in");

	int sum = 0;
	int max_sum[3] = { 0 };
	char buffer[SIZE];
	while (fgets(buffer, SIZE, in)) {
		if (buffer[0] == '\n') {
			if (sum > max_sum[0]) {
				max_sum[2] = max_sum[1];
				max_sum[1] = max_sum[0];
				max_sum[0] = sum;
			}
			else if (sum > max_sum[1]) {
				max_sum[2] = max_sum[1];
				max_sum[1] = sum;
			}
			else if (sum > max_sum[2]) {
				max_sum[2] = sum;
			}
			sum = 0;
		}
		else {
			buffer[strlen(buffer) - 1] = 0;
			int value = atoi(buffer);
			sum += value;
		}
	}

	fclose(in);
	int result = max_sum[0] + max_sum[1] + max_sum[2];
	printf_s("%d\n", result);
}

static int main(void) {
	first();
	second();
	return 0;
}