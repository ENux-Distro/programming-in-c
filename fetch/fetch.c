#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int os_name() {

	char *args[] = {"grep", "NAME", "/etc/os-release", NULL};
	pid_t fork_result = fork();
	if (fork_result == 0) {
		 execvp(args[0], args);
	} else {
		siginfo_t info;
		waitid(P_ALL, fork_result, &info, WEXITED);
	}
}
int kernel() {

	struct utsname info;

	if (uname(&info) == -1) {
  	  perror("uname");
      return -1;
	}

	write(1, info.release, strlen(info.release));
	write(1, "\n", 1);

}

int uptime() {

	char *args[] = {"uptime", "-p", NULL};
	pid_t fork_result = fork();
	if (fork_result == 0) {
		execvp(args[0], args);
	} else {
		siginfo_t info;
		waitid(P_ALL, fork_result, &info, WEXITED);
	}

}

int shell() {

    char *shell_path = getenv("SHELL");
    if (!shell_path) {
    	write(1, "No proper shell detected", 24);
        return 0;
    }

	printf("%s\n", shell_path);
}

int pm(const char *command) {

    if (!command || strlen(command) == 0) {
        return 0;
    }

    char *path_env = getenv("PATH");
    if (!path_env) {
        return 0;
    }

    char *path_copy = strdup(path_env);
    if (!path_copy) {
        return 0;
    }

    int found = 0;
    char full_path[1024];

    char *dir = strtok(path_copy, ":");
    while (dir != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0) {
            found = 1;
            break;
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return found;
}


int main() {

	write(1, "OS ", 3);
	os_name();

	write(1, "KERNEL ", 7);
	kernel();

	write(1, "UPTIME ", 7);
	uptime();

	// package manager check block
	// begin
	write(1, "PACKAGE MANAGERS=", 17);
	if (pm("apt")) {
		write(1, "apt ", 4);
	}

	if (pm("pacman")) {
		write(1, "pacman ", 8);
	}

	if (pm("nix")) {
		write(1, "nix ", 4);
	}

	if (pm("dnf")) {
		write(1, "dnf ", 4);
	}

	if (pm("flatpak")) {
		write(1, "flatpak ", 8);
	}

	if (pm("apk")) {
		write(1, "apk ", 4);
	}

	if (pm("xbps-install")) {
		write(1, "xbps ", 5);
	}

	if (pm("zypper")) {
		write(1, "zypper\n", 8);
	}

	// end
	write(1, "SHELL=", 6);
	shell();
}
