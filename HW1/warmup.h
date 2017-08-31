// John Espenhahn - Honor pledge

#ifndef WARMUP_H
#define WARMUP_H

#include <stdio.h>
#include <stdbool.h>

#ifndef LINE_LEN
// To allow debugging with shorter lines add guard
#define LINE_LEN 80
#endif

struct Line {
	int buffer[LINE_LEN];
	int idx;
	int next_c;
};

bool process_char(struct Line* line, FILE* in);
void append(struct Line* line, int c);
void print(struct Line* line, FILE* out);
void reset(struct Line* line);

// Precondition: line->next_c is the last read but unprocess char from in
// Postcondition: line->next_c is the last read but unprocessed char from in
// Return: true if should continue processing, false if shouldn't (EOF or EOL)
bool process_char(struct Line* line, FILE* in) {
	int c = line->next_c;
	if (c < 0) {
		return false;
	} else if (line->idx == LINE_LEN) {
		return false; 
	} else if (c == '\n') {
		append(line, ' ');
	} else if (c == '*') {
		line->next_c = fgetc(in);
		if (line->next_c == '*') {
			// Got double **
			append(line, '^');
		} else {
			// Got * followed by {something else}
			// Append * then process {something else}
			append(line, '*');
			return process_char(line, in);
		}
	} else {
		append(line, line->next_c);
	}

	line->next_c = fgetc(in);
	return true;
}

void append(struct Line* line, int c) {
	line->buffer[line->idx++] = c;
}

void print(struct Line* line, FILE* out) {
	for (int i = 0; i < LINE_LEN; i++) {
		fputc(line->buffer[i], out);
	}

	fputc('\n', out);
}

void reset(struct Line* line) {
	line->idx = 0;
}

#endif
