#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<malloc.h>


void filtr (char* command) {
	FILE *f = popen(command, "r");
	if (f == NULL) {
		perror(command);
		return;
	}
	int col_str = 0;
	char c;
	char* buf = malloc(1);	
	if (buf == NULL) {
		perror(buf);
		pclose(f);
		return;
	}
	c = fgetc(f);
	while (!feof(f)) {
		buf[0] = c;
		write(1, buf, 1);
		if (c == '\n')
			col_str++;
		c = fgetc(f);
	}
	pclose(f);
	printf("Количество строк равно: %d\n", col_str);
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Недостаточно аргументов");
		return 1;
	}
	int i, reslen = 0;
	for (i = 1; i < argc; i++) 
		reslen += strlen(argv[i]) + 1;
	char* arguments = malloc(reslen);
	for (i = 1; i < argc - 1; ++i) {	
		strcat(arguments, argv[i]);
		strcat(arguments, " ");
	}
	strcat(arguments, argv[i]);
	arguments[reslen - 1] = 0;
	filtr(arguments);
	return 0;
}
