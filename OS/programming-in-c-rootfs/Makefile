iso:

		mkdir -p iso/boot/grub
		mkdir -p iso/output
		cp boot/bzImage iso/boot/bzImage
		cp boot/init.cpio iso/boot/bzImage
		cp boot/grub/grub.cfg iso/boot/grub/grub.cfg
		grub-mkrescue iso -o iso/output/programming-in-c.iso
		echo "ISO Created at iso/output/programming-in-c.iso"

clean:
		rm -rf iso


clear:

		rm -rf iso

run:
		qemu-system-x86_64 -cdrom iso/output/programming-in-c.iso
