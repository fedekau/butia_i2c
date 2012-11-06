#
# Makefile for the USB4all driver for the 2.6.6+  kernel
#
#
#   To load the module 
#         su 
#         insmod usb4all.ko
#
#   To unload 
#         rmmod usb4all
#
#   Check /sys/bus/usb to see if the module was loaded.
#
#   For output see /var/log/messages

obj-m	:= usb4all.o


KDIR    := /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

