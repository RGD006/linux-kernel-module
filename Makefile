
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile

obj-m   := hello1.o hello2.o
EXTRA_CFLAGS += -g

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD \
		EXTRA_CFLAGS="-I$(PWD)/inc -g" \

	$(CROSS_COMPILE)strip --strip-debug hello1.ko hello2.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
