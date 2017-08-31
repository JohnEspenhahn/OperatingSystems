// John Espenhahn - Honor pledge
// Onyen: jesp
// PID: 720511503

#include <stdio.h>
#include <stdbool.h>
#include "warmup.h"

void main() {
	struct Line line;
	reset(&line);

	line.next_c = fgetc(stdin);
	while (line.next_c != EOF) {
		// Keep processing chars while not EOF nor EOL
		while (process_char(&line, stdin)) { }
		
		// Got a full LINE_LEN characters
		if (line.idx == LINE_LEN) 
			print(&line, stdout);

		reset(&line);
	}
}

