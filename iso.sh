#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/minervaos.kernel isodir/boot/minervaos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "minervaos" {
	multiboot /boot/minervaos.kernel
}
EOF
if grub-file --is-x86-multiboot isodir/boot/minervaos.kernel; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
grub-mkrescue -o minervaos.iso isodir
