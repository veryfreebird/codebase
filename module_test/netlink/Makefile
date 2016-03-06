obj-m := testnetlink.o
modules-objs := testnetlink.o
KERNELDIR := /lib/modules/`uname -r`/build 
PWD := $(shell pwd) 

default: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules 

modules_install: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
