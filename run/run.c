#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	if (argc < 2) {

		write(1, "usage: run <command>\n", 21);
		return 1;

	}

	char **args = &argv[1];

	pid_t fork_result = fork();

	if (fork_result == 0) {

		execvp(args[0], args);
		perror("do");
		exit(127);
	}

	int status;
	waitpid(fork_result, &status, 0);
	if (WIFSIGNALED(status)) {
		printf("\nkilled by signal %d\n", WTERMSIG(status));
	}
	return WEXITSTATUS(status);

}
