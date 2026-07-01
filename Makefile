all:

		make -C shell cc
		make -C fetch cc
		make -C run cc
		echo "FHS contains folders my guy"
		make -C init cc

		tar xf OS/programming-in-c-rootfs.tar.xz -C OS/
		make -C OS/programming-in-c iso


shell:

		make -C shell cc

fetch:

		make -C fetch cc

run:

		make -C run cc

fhs:

		echo "FHS contains folders my guy"

init:

		make -C init cc

os:

		tar xf OS/programming-in-c-rootfs.tar.xz -C OS/
		make -C OS/programming-in-c iso
