#obj-m is a special variable to indentify the obj files.
obj-m :=globalfifo.o

PWD :=$(shell pwd)
#KERNELDIR :=/lib/modules/4.9.4/build
#KERNELDIR :=/lib/modules/4.4.0-57-generic/build
KERNELDIR :=/lib/modules/$(shell uname -r)/build
#KERNELDIR :=/usr/src/linux-headers-4.4.0-57-generic/
#make :
# -C enter the kernel directory
# M=$(PWD) just a variable definition.the kernel makefile will use it like: KBUILD_EXTMOD := $(M)
# modules identify will make the modules.just like make clean
all:
	make -C $(KERNELDIR) M=$(PWD) modules

.PHONY: clean test inmod outmod
clean:
	rm -rf *.o *.ko *mod* *.cmd .globalfifo* Module.symvers .tmp* test

test: test.c
	gcc $^ -o $@

inmod:
	insmod globalfifo.ko
	mknod /dev/globalfifo c 246 0
outmod:
	rmmod globalfifo
	rm /dev/globalfifo

