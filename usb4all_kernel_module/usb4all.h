/*
 * USB4all driver - 1.0
 *
 * Copyright (C) 2007 Andres Aguirre, Daniel Pedraja
 * Copyright (C) 2001-2004 Greg Kroah-Hartman (greg@kroah.com)
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 */

//#include <linux/config.h> para versiones de kernels viejos
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/mutex.h>
#include <linux/list.h>
#include <linux/delay.h>
//#include <linux/smp_lock.h>
//#include <linux/usb/ch9.h>


/* Define these values to match your devices */
#define USB4all_VENDOR_ID	 0x04d8
#define USB4all_PRODUCT_ID	 0x000c

/* Params for SET_TRANSFER_TYPE IOCTL */
#define CTRL	0
#define INT	1
#define BULK	2
#define ISO	3

/* IOCTL commands */
#define GET_DEVICE_DESCRIPTOR	 	0x0001
#define SET_DESC_INDEX		 	0x0002
#define SET_IN_ENDPOINT		 	0x0003
#define SET_OUT_ENDPOINT   	 	0x0004
#define GET_ENDPOINT_DESCRIPTOR  	0x0005
#define GET_INTERFACE_DESCRIPTOR 	0x0006
#define GET_CONFIGURATION_DESCRIPTOR 	0x0007
#define SET_TRANSFER_TYPE	 	0x0008
#define SET_TIMEOUT			0x0009
#define GET_STRING_DESCRIPTOR		0x000a
#define DEBUG_STRING_DESCRIPTOR		0x000b

/* Get a minor range for your devices from the usb maintainer */
#define USB4all_MINOR_BASE	192

/* our private defines. if this grows any larger, use your own .h file */
#define MAX_TRANSFER		( PAGE_SIZE - 512 )
#define WRITES_IN_FLIGHT	8

/* urb list node definition */
struct urb_node{
    struct urb * request;
    struct list_head list;
};

/* Structure to hold all of our device specific stuff */
struct usb_U4all {
	struct usb_device *	udev;			/* the usb device for this device */
	struct usb_interface *	interface;		/* the interface for this device */
	struct semaphore	limit_sem;		/* limiting the number of writes in progress */
	unsigned char *		in_buffer;		/* the buffer to receive data */
	size_t			in_size;		/* the size of the receive buffer */
	__u8			in_endpointAddr;	/* the address of the bulk in endpoint */
	__u8			out_endpointAddr;	/* the address of the bulk out endpoint */
	struct kref		kref;
    //isochronous I/O specific fields
	struct list_head free_read_urbs;                /* inactive urbs ready for read requests */
	struct list_head busy_read_urbs;                /* urbs submitted in read requests */
    wait_queue_head_t read_wait;                    /* for the read method to wait for requested data */
    int current_urb_readptr;                        /* ptr to next byte to read  in the current urb*/
    int urbBufferSize;                              /* size of the buffer to alloc for each urb*/
    int nurbs;                                      /* number of urbs allocated for reading*/
};

struct endpointSizeItem {
	u_int16_t wMaxPacketSize;
	u_int8_t  bEndpointAddress;
};

