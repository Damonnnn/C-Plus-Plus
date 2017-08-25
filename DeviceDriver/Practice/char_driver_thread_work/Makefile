
#obj-m is a special variable to indentify the obj files.
obj-m :=damonDriver.o
PWD :=$(shell pwd)
KERNELDIR :=/lib/modules/$(shell uname -r)/build
#KERNELDIR :=/usr/src/linux-headers-4.4.0-57-generic/
#make :
# -C enter the kernel directory
# M=$(PWD) just a variable definition.the kernel makefile will use it like: KBUILD_EXTMOD := $(M)
# modules identify will make the modules.just like make clean
all:
	make -C $(KERNELDIR) M=$(PWD) modules

.PHONY: clean
clean:
	rm -rf *.o *.ko *mod* *.cmd .damon* Module.symvers .tmp*

