#include <sys/mount.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

	int mount_tmpfs()
	{
		const char *src = "none";
		const char *target = "/temp";
		const char *type = "none";

	    unsigned long flags = MS_NODEV
	                        | MS_NOSUID
	                        | MS_NOEXEC;

		const char *options = "size=50M,mode=0700";

	    if (mount(src, target, type, flags, options) == 0) {
	        return 0;
	    } else {
	        fprintf(stderr, "Mounting /tmp failed: %s\n", strerror(errno));
	        return -1;
	    }

	}

	int mount_dev()
	{
		const char *source = "none";
		const char *target = "/dev";
	    const char *filesystemtype = "none";
	    unsigned long mountflags = 0;
	    const void *data = NULL;

	    int result = mount(source, target, filesystemtype, mountflags, data);

	    if (result == 0) {
	        printf("Successfully mounted %s to %s\n", source, target);
	    } else {
	        perror("Mounting /dev failed");
	        printf("Error code: %d\n", errno);
	        return -1;
	    }
	}

	int mount_proc()
	{

		const char *source = "none";
		const char *target = "/proc";
		const char *filesystemtype = "none";
		unsigned long mountflags = 0;
		const void *data = NULL;
		if (mount(source, target, filesystemtype, mountflags, data) != 0) {
        	fprintf(stderr, "Failed to mount %s at %s: %s\n",
                filesystemtype, target, strerror(errno));
        	return EXIT_FAILURE;
    	}

    	printf("Successfully mounted %s at %s.\n", filesystemtype, target);
   		return EXIT_SUCCESS;

	}

	int mount_sys()
	{
		const char *source = "none";
	    const char *target = "/sys";
	    const char *filesystemtype = "none";
	    unsigned long mountflags = 0;
	    const void *data = NULL;

	    if (mount(source, target, filesystemtype, mountflags, data) != 0) {
	        perror("Failed to mount /sys");
	        return EXIT_FAILURE;
	    }

	    printf("Successfully mounted sysfs to /sys\n");
	    return EXIT_SUCCESS;
	}

	int start_sh()
	{
    setenv("PATH", "/programs:/sprograms", 1);

	char *argv[] = {"/programs/sh", NULL};
	char *envp[] = {NULL};
	execve("/programs/sh", argv, envp);
	}

	mount_tmpfs();
	mount_dev();
	mount_proc();
	mount_sys();
	start_sh();
}
