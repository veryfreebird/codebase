obj-m := mymod.o                   #要生成的模块名       
modules-objs:= mymod.o        #生成这个模块名所需要的目标文件   
KDIR := /lib/modules/`uname -r`/build 
PWD := $(shell pwd)   

default:  
	make -C $(KDIR) M=$(PWD) modules   

clean:  
	rm -rf *.o *.ko *.mod.c *.tmp_versions
	rm -rf Module.*
	rm -rf modules.*
