#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>


void filtr (char* argv[]) {
	int col_str = 0;
	int n;
	int fd[2];
	if (pipe(fd) < 0) {
		perror("pipe error");
		return;
	}
	if (!fork()) {
		close(fd[0]);
		dup2(fd[1], 1);
		execvp(argv[1], argv + 1);
		close(fd[1]);
	} else {
		close(fd[1]);
		char* buf = malloc(1);	
		if (buf == NULL) {
			perror(buf);
			close(fd[0]);
			return;
		}
		while ((n = read(fd[0], buf, 1)) != 0) {
			write(1, buf, n);
			if (buf[0] == '\n')
				col_str++;
		}
		close(fd[0]);
		printf("Количество строк равно: %d\n", col_str);
	}
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Недостаточно аргументов");
		return 1;
	}
	filtr(argv);
	return 0;
}
