CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

#MAJOR = 201

TARGET1 = pim
obj-m += $(TARGET1).o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.o *.cmd .*.cmd *.order *.mod.c .*.o.d
	rm -fR .tmp*

disclean: clean
	rm -f *.ko *.symvers

load:
#	sudo depmod -b $(PWD) $(TARGET1).ko
#	sudo modprobe -av -d $(PWD) $(TARGET1).ko
	sudo insmod $(TARGET1).ko
#sudo dmesg -c
#mknod -m0666 /dev/zzzz c $(MAJOR) 0

unload:
	sudo rmmod $(TARGET1).ko
#sudo dmesg
#rm /dev/zzzz
