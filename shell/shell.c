#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define MAX_INPUT 1024

int builtin_cd(char **args) {
	char *target_dir = NULL;
	char cwd[1024];

	if (args[1] == NULL) {
		target_dir = getenv("HOME");
		if (target_dir == NULL) {
			fprintf(stderr, "cd: HOME environment variable not set\n");
			return 1;
		}
	}
	else if (strcmp(args[1], "-") == 0) {
		target_dir = getenv("OLDPWD");
		if (target_dir == NULL) {
			fprintf(stderr, "cd: OLDPWD not set\n");
			return 1;
		}
		printf("%s\n", target_dir);
	}
	else if (strcmp(args[1], "~") == 0) {
		target_dir = getenv("HOME");
	}
	// Standard path provided
	else {
		target_dir = args[1];
	}

	// Capture the current working directory BEFORE changing it (to save as OLDPWD)
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("cd: getcwd failed");
		return 1;
	}

	// Execute the actual directory switch
	if (chdir(target_dir) != 0) {
		perror("cd"); // Will output "cd: No such file or directory", etc.
		return 1;
	}

	// Update environment bookkeeping variables for system accuracy
	setenv("OLDPWD", cwd, 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		setenv("PWD", cwd, 1);
	}

	return 0;
}

int builtin_export(char **argv) {
    // If no argument is provided, print an error or list variables
    if (argv[1] == NULL) {
        fprintf(stderr, "export: expected argument format: NAME=VALUE\n");
        return 1;
    }

    // Find the '=' sign separating the variable name and its value
    char *eq_sign = strchr(argv[1], '=');
    if (eq_sign == NULL) {
        fprintf(stderr, "export: invalid syntax. Use NAME=VALUE\n");
        return 1;
    }

    // Split the string into two parts at the '=' position
    *eq_sign = '\0';
    char *var_name = argv[1];
    char *var_value = eq_sign + 1;

    // Modify the parent process environment state directly
    if (setenv(var_name, var_value, 1) != 0) {
        perror("export execution failed");
        return 1;
    }

    printf("Successfully exported: %s=%s\n", var_name, var_value);
    return 0;
}

int main(void) {

	for (;;) {
		write(1, "sh> ", 4);

		char command[MAX_INPUT];

		int count = read(0, command, MAX_INPUT - 1);
		if (count <= 0) break;
		command[count - 1] = '\0';

		if (strcmp(command, "exit") == 0) {
			break; // Break out of the loop
		}

		// Tokenize the command line into args[]
		char *args[64];
		int i = 0;

		char *token = strtok(command, " \t");
		while (token != NULL && i < 63) {
			args[i++] = token;
			token = strtok(NULL, " \t");
		}
		args[i] = NULL;

		// Empty line, nothing to do
		if (args[0] == NULL) continue;

		// cd must run in the parent, not a child process
		if (strcmp(args[0], "cd") == 0) {
			builtin_cd(args);
			continue;
		}
		if (strcmp(args[0], "export") == 0) {
			builtin_export(args);
			continue;
		}


		pid_t fork_result = fork();
		if (fork_result == 0) {
			// child
			execvp(args[0], args);

			perror("execvp");
			exit(127);

		} else {
			// parent
			siginfo_t info;
			waitid(P_ALL, 0, &info, WEXITED);
		}
	}

	return 0;
}
