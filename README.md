# Programming In C

This my GitHub repo where I upload my fairly nice projects written in C. Here are everything that's in this repo:

- Fetch: A custom fetcher tool written in C that shows your:
	- OS name (via grepping NAME on /etc/os-release)
	- Kernel version (via uname(2))
	- Uptime (via uptime -p)
	- Available package managers (via a custom function to find if the package manager is available in your system)
	- Default shell (via printf(3)'ing the system's $SHELL variable, which used getenv(3) to get the $SHELL variable)

- Init: (Not to get confused with [init.c](https://github.com/ENux-Distro/init.c) A simple init that mounts the virtual fs's and starts the shell. It assumes a custom FHS, which will be uploaded onto this repository later.

- Run: A fork + execvp + waitid wrapper, that runs your desired command without replacing the current running shell process

- Shell: A custom shell with support for:
	- cd
	- export
	- exit
	- CTRL + D making the shell exit
	- PATH support (with execvp)
	- Support for stuff like ``ls -lh``
And, the shell.c is only 142 lines.

### Things that will be added in the future

- FHS: A custom FHS, similar to GoboLinux's, but still Unix'y
- NamelessOS, featuring the FHS, Init, Shell, Fetch and Run command
- NamelessOS's ISO image and Tar archive

### Contributing

If you want to contribute to my Programming in C journey, follow these steps:

- Fork this repository and add your patches
- Create an pull request
- Make sure your pull request explains what you've done, with clear toning
- I'll review your pull request, and either approve it, or don't

### If You Use an AI Agent to Commit to This Repository

If you want to contribute using an AI assistant, check Claude.md; that tells your AI assistant what it can do and cannot.
