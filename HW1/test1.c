#define LINE_LEN 4

#include "warmup.h"
#include <assert.h>
#include <stdio.h>

void test_process_char() {
	// Setup	
	FILE *fp;

	struct Line line;
	reset(&line);

	// Test basic newline and double-*
	fp = tmpfile();
	fputs("\na**", fp);
	fseek(fp, 0, SEEK_SET);
	line.next_c = fgetc(fp);	

	process_char(&line, fp);
	assert(line.buffer[line.idx-1] == ' ');	

	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == 'a');

	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');	

	assert(process_char(&line, fp) == false);

	// Reset
	reset(&line);

	// Test  double-* past end
	fclose(fp);
	fp = tmpfile();
	fputs("ab******234", fp);
	fseek(fp, 0, SEEK_SET);
	line.next_c = fgetc(fp);

	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == 'a');
	assert(line.next_c == 'b');
	
	assert(process_char(&line, fp) == true);
	assert(line.next_c == '*');
	assert(line.buffer[line.idx-1] == 'b');	

	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');

	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');

	assert(line.next_c == '*');
	assert(line.idx == LINE_LEN);
	assert(process_char(&line, fp) == false);
	assert(line.next_c == '*');
	assert(line.idx == LINE_LEN);
	
	// Test reset
	reset(&line);
	assert(line.idx == 0);
	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');
	process_char(&line, fp);
	assert(line.buffer[line.idx-1] == '2');
	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '3');
	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '4');
	assert(process_char(&line, fp) == false);
	assert(line.idx == LINE_LEN);

	// Reset
	fclose(fp);
	fp = tmpfile();
	reset(&line);
	
	// Test not full
	fputs("******", fp);
	fseek(fp, 0, SEEK_SET);
	line.next_c = fgetc(fp);

	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');
	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');
	assert(process_char(&line, fp) == true);
	assert(line.buffer[line.idx-1] == '^');
	assert(process_char(&line, fp) == false);
	assert(line.idx < LINE_LEN);
}

int main() {
	test_process_char();

	printf("done\n");
}
