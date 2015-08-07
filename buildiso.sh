rm -f isodir/boot/kal.bin
rm -f kal.iso
cp bin/kal.bin isodir/boot/kal.bin
grub-mkrescue -o kal.iso isodir	
