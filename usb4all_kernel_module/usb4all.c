/*
 * USB4all driver - 1.0
 *
 * Copyright (C) 
 *	2001-2004 Greg Kroah-Hartman (greg@kroah.com)
 *	2007 Andres Aguirre, Daniel Pedraja
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 */


#include "usb4all.h"

/* table of devices that work with this driver */
static const struct usb_device_id U4all_table [] = {
	{ USB_DEVICE(USB4all_VENDOR_ID, USB4all_PRODUCT_ID) },
	{ }					/* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, USB4all_table);

#define to_U4all_dev(d) container_of(d, struct usb_U4all, kref)

static struct usb_driver U4all_driver;

//indice del descriptor pedido mediante ioctl
unsigned char descindex = 0;

struct endpointSizeItem endpointSizes[15];

static int timeout = 10000;
static int transferType = BULK;
static void unicode_to_ascii            (char *string, __le16 *unicode, int unicode_size);

static void U4all_delete(struct kref *kref)
{
	struct usb_U4all *dev = to_U4all_dev(kref);

	usb_free_urb(dev->bulk_in_urb);
	usb_put_dev(dev->udev);
	kfree(dev->bulk_in_buffer);
	kfree(dev);
}

static int U4all_open(struct inode *inode, struct file *file)
{
	struct usb_U4all *dev;
	struct usb_interface *interface;
	int subminor;
	int retval = 0;

	subminor = iminor(inode);

	interface = usb_find_interface(&U4all_driver, subminor);
	if (!interface) {
		err("%s - error, can't find device for minor %d",
		     __func__, subminor);
		retval = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(interface);
	if (!dev) {
		retval = -ENODEV;
		goto exit;
	}

	/* increment our usage count for the device */
	kref_get(&dev->kref);

	/* lock the device to allow correctly handling errors
	 * in resumption */
	mutex_lock(&dev->io_mutex);

	if (!dev->open_count++) {
		retval = usb_autopm_get_interface(interface);
			if (retval) {
				dev->open_count--;
				mutex_unlock(&dev->io_mutex);
				kref_put(&dev->kref, skel_delete);
				goto exit;
			}
	} /* else { //uncomment this block if you want exclusive open
		retval = -EBUSY;
		dev->open_count--;
		mutex_unlock(&dev->io_mutex);
		kref_put(&dev->kref, skel_delete);
		goto exit;
	} */
	/* prevent the device from being autosuspended */

	/* save our object in the file's private structure */
	file->private_data = dev;
	mutex_unlock(&dev->io_mutex);

exit:
	return retval;
}

static int U4all_release(struct inode *inode, struct file *file)
{
	struct usb_U4all *dev;

	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;

	/* allow the device to be autosuspended */
	mutex_lock(&dev->io_mutex);
	if (!--dev->open_count && dev->interface)
		usb_autopm_put_interface(dev->interface);
	mutex_unlock(&dev->io_mutex);

	/* decrement the count on our device */
	kref_put(&dev->kref, U4all_delete);
	return 0;
}

static void U4all_iso_read_complete(struct urb * purb, struct pt_regs *regs)
{
        struct usb_U4all * dev = purb->context;
        int i;
        int len;
        int dst = 0;
        int packetSize;
        void *buf = purb->transfer_buffer;

        //TODO revisar caso lastframe
        packetSize = dev->in_size;//every frame length is equals to packetSize

        // process if URB was not killed
        if(purb->status != -ENOENT){
            //comprimo segmentos leidos en uno solo
            for(i = 0; i < purb->number_of_packets; i++)
                    if(!purb->iso_frame_desc[i].status) {
                            len = purb->iso_frame_desc[i].actual_length;
                            if(len <= packetSize) {
                                    memcpy (buf + dst, buf + purb->iso_frame_desc[i].offset, len);
                                    dst += len;
                            }else//TODO es necesario este control???
                                    err("usb4all_iso_complete: invalid len %d", len);
                    }else
                            warn("usb4all_iso_complete: corrupted packet status: %d", purb->iso_frame_desc[i].status);

            if (dst != purb->actual_length)
                    err("dst!=purb->actual_length:%d!=%d", dst, purb->actual_length);
            //err("salgo read complete leido %d",purb->actual_length);
        }else
            err("salgo read complete ENOENT");
        
        wake_up (&dev->read_wait);
}

//moves src's head to dest's tail
static int U4all_switch_urb_list(struct list_head *dest, struct list_head *src){
	struct list_head *temp;


	if(list_empty(src)){
        return -1;
	}
	temp = src->next;
	list_move_tail(temp, dest);

    return 0;
}

static int U4all_destroy_urb_list(struct list_head * list){
	struct urb_node * node;
	struct list_head *temp;
	struct list_head *p;

	for(p = list->next; p != list;){
		node = list_entry (p, struct urb_node, list);
        //libero memoria reservada
		kfree(node->request->transfer_buffer);
		//devuelvo urb
		usb_free_urb(node->request);
		temp = p;
		p = p->next;
		list_del (temp);
		kfree (node);
	}

	return 0;
}
        
        
static int U4all_iso_clean_read_urbs( struct usb_U4all * dev ){
       U4all_destroy_urb_list(&dev->free_read_urbs); 
       U4all_destroy_urb_list(&dev->busy_read_urbs); 
       return 0;
}        
        

static int U4all_iso_init_read_urbs( struct usb_U4all * dev )
{
    
    
    /*
     * PARAMETROS PARA HACERLO GENERICO
     * dev->nurbs ok
     * dev->urbBufferSize OK
     * urbFlags ?
     */
     
    
	struct urb_node * node;
	unsigned int pipe = usb_rcvisocpipe (dev->udev, dev->in_endpointAddr);
	int packetSize = dev->in_size;//usb_maxpacket (dev->udev, pipe, usb_pipeout (pipe));
	int packets = dev->urbBufferSize/packetSize;
	int i,j, lastPacketSize = dev->urbBufferSize%packetSize;
    int interval = 255 ; //TODO levantar del dev                     
    
    if(lastPacketSize > 0)
        packets++;                      
    
	for(j = 0;j < dev->nurbs; j++) {
        node = (struct  urb_node *)kmalloc(sizeof (struct urb_node), GFP_KERNEL);
        if (!node) {
            goto err;
        }
        memset (node, 0, sizeof (struct urb_node));
        node->request = usb_alloc_urb(packets, GFP_KERNEL);
        if (!node->request ) {
            err("usb4all: alloc_urb == NULL");
            kfree(node);
            goto err;
        }

        node->request->transfer_buffer = kmalloc(dev->urbBufferSize, GFP_KERNEL);
        if (!node->request->transfer_buffer) {
            kfree (node->request);
            kfree (node);
            //err("kmalloc(%d)==NULL", dev->urbBufferSize);
            goto err;
        }

        node->request->transfer_buffer_length = dev->urbBufferSize;
        node->request->number_of_packets = packets;
        node->request->complete = U4all_iso_read_complete;
        node->request->context = dev;
        node->request->dev = dev->udev;
        node->request->pipe = pipe;
        node->request->transfer_flags = URB_ISO_ASAP;
    	if (dev->udev->speed == USB_SPEED_HIGH)
    		node->request->interval = 1 << (interval - 1);
    	else
    		node->request->interval = interval;
    	err("INTERVAL: %d",node->request->interval);	
    	node->request->start_frame = -1;

        for(i = 0; i < packets-1; i++){
            node->request->iso_frame_desc[i].offset = i * packetSize;
            node->request->iso_frame_desc[i].length = packetSize;
        }
        node->request->iso_frame_desc[i].offset = i * packetSize;
        if(lastPacketSize > 0){
            node->request->iso_frame_desc[i].length = lastPacketSize;
        }else{
            node->request->iso_frame_desc[i].length = packetSize;
        }

        list_add_tail (&node->list, &dev->free_read_urbs);
	}
	return 0;

    err:
        U4all_iso_clean_read_urbs (dev);
        return -ENOMEM;
}

static int U4all_iso_read_init( struct usb_U4all * dev )
{
    if(list_empty(&dev->free_read_urbs)&&list_empty(&dev->busy_read_urbs)) {
        if (U4all_iso_init_read_urbs (dev) < 0)
            return -ENOMEM;
    }
    return 0;
}

static int U4all_iso_request_data( struct usb_U4all * dev ) 
{
        struct urb_node * temp;
        int ret;

        while (!U4all_switch_urb_list(&dev->busy_read_urbs, &dev->free_read_urbs)) {
            temp = list_entry(dev->busy_read_urbs.prev, struct urb_node, list);

            ret = usb_submit_urb (temp->request, GFP_KERNEL);//TODO ver en el cap 13 si corresponde esta FLAG
            if(ret){
                //err("usb_submit_urb returned: %d", ret);
                //TODO devolver urb a la lista de free
                break;
            }
        }
        return 0;
}

static ssize_t U4all_read(struct file *file, char *buffer, size_t count, loff_t *ppos)
{
	struct usb_U4all *dev;
	int retval = 0;
	int bytes_read = 0;
    int urb_count;
    int curr_count;
	
	struct urb * current_urb = 0;
	struct urb_node * unode = 0;
    
	dev = (struct usb_U4all *)file->private_data;
	
	switch(transferType){
        case BULK:
            /* do a blocking bulk read to get data from the device */
            retval = usb_bulk_msg(dev->udev,
            		      usb_rcvbulkpipe(dev->udev, dev->in_endpointAddr),
            		      dev->in_buffer,
            		      min(dev->in_size, count),
            		      &bytes_read, 10000);
            /* if the read was successful, copy the data to userspace */
            if (!retval) {
                    if (copy_to_user(buffer, dev->in_buffer, bytes_read))
                            retval = -EFAULT;
                    else
                            retval = bytes_read;
            }
            break;
        case ISO:
             //err("Arrnaca read ISO\n");
            U4all_iso_read_init(dev);
             //err("paso read INIT\n");
            dev->current_urb_readptr = 0;
            while(count > 0){
//             //err("vuelta loop count= %d\n",count);
                U4all_iso_request_data(dev);                                       
//             //err("paso requestData \n");
                //get current urb 
                unode = list_entry(dev->busy_read_urbs.next, struct urb_node, list);
                current_urb = unode->request;

                //if not completed, wait
          		if(current_urb->status == -EINPROGRESS){
                    if(file->f_flags & O_NONBLOCK){
                        if(!bytes_read)
                            return -EAGAIN;
                        return bytes_read;             
                    }
             //err("me voy a bloquear\n");

                    //wait for the urb to complete
                    interruptible_sleep_on(&dev->read_wait);
             //err("sali bloqueo\n");

                    if(signal_pending(current)){
                        if(!bytes_read)
                            return -ERESTARTSYS;
                        return bytes_read;             
                    }
                    
                    //ready to start reading next urb
                    dev->current_urb_readptr = 0;
                }
                //completed urb available, process it
                urb_count = current_urb->actual_length - dev->current_urb_readptr;	 
                curr_count = min(count, (size_t)urb_count);
                
        		if (copy_to_user(buffer, current_urb->transfer_buffer + dev->current_urb_readptr, curr_count)) {
        			//err("read: copy_to_user failed");
        			if (!bytes_read)
        				return -EFAULT;
                                return bytes_read;             
        		}
        
        		dev->current_urb_readptr += curr_count;
        		count -= curr_count;
        		buffer += curr_count;
        		bytes_read += curr_count;
        
        		if(dev->current_urb_readptr == current_urb->actual_length){
        			// finished, free urb and start next
        			if (U4all_switch_urb_list (&dev->free_read_urbs, &dev->busy_read_urbs))
        				//err("ERRORRRRRRR");
        			dev->current_urb_readptr = 0;
        		}
                

            }       
            retval = bytes_read;       
            break; 
    	default:
    		return -ENOSYS;
             
    }                         
    return retval;
}

static void U4all_write_bulk_callback(struct urb *urb)
{
	struct usb_U4all *dev;

	dev = urb->context;

	/* sync/async unlink faults aren't errors */
	if (urb->status) {
		if (!(urb->status == -ENOENT ||
		    urb->status == -ECONNRESET ||
		    urb->status == -ESHUTDOWN))
			err("%s - nonzero write bulk status received: %d",
			    __func__, urb->status);

		spin_lock(&dev->err_lock);
		dev->errors = urb->status;
		spin_unlock(&dev->err_lock);
	}

	/* free up our allocated buffer */
	usb_free_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
}

static void U4all_write_iso_callback(struct urb *urb, struct pt_regs *regs)
{
	struct usb_U4all *dev;

	dev = (struct usb_U4all *)urb->context;

	/* sync/async unlink faults aren't errors */
	if (urb->status && 
	    !(urb->status == -ENOENT || 
	      urb->status == -ECONNRESET ||
	      urb->status == -ESHUTDOWN)) {
		//err("%s - nonzero write iso status received: %d",
		   // __FUNCTION__, urb->status);
	}
	//err("%s - iso status received: %d", __FUNCTION__, urb->status);
    //err("%s - Se escribio: %d", __FUNCTION__,urb->actual_length );
//	//err("%s - iso_frame_desc status received: %d", __FUNCTION__, urb->iso_frame_desc[0].status);
//    //err("%s - iso_frame_desc Se escribio: %d", __FUNCTION__,urb->iso_frame_desc[0].actual_length );


	/* free up our allocated buffer */
	usb_buffer_free(urb->dev, urb->transfer_buffer_length, 
			urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
}


static ssize_t U4all_write(struct file *file, const char *user_buffer,
			  size_t count, loff_t *ppos)
{
	struct usb_U4all *dev;
	int retval = 0;
	struct urb *urb = NULL;
	int nurbs, i, rem, curr_count;
	int interval = 1;//TODO
	char *buf = NULL;
	size_t writesize = min(count, (size_t)MAX_TRANSFER);

	dev = file->private_data;

	/* verify that we actually have some data to write */
	if (count == 0)
		goto exit;
/*	switch(transferType){
        case BULK:  /*


	/*
	 * limit the number of URBs in flight to stop a user from using up all
	 * RAM
	 */
	if (!(file->f_flags & O_NONBLOCK)) {
		if (down_interruptible(&dev->limit_sem)) {
			retval = -ERESTARTSYS;
			goto exit;
		}
	} else {
		if (down_trylock(&dev->limit_sem)) {
			retval = -EAGAIN;
			goto exit;
		}
	}

	spin_lock_irq(&dev->err_lock);
	retval = dev->errors;
	if (retval < 0) {
		/* any error is reported once */
		dev->errors = 0;
		/* to preserve notifications about reset */
		retval = (retval == -EPIPE) ? retval : -EIO;
	}
	spin_unlock_irq(&dev->err_lock);
	if (retval < 0)
		goto error;

	/* create a urb, and a buffer for it, and copy the data to the urb */
	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		retval = -ENOMEM;
		goto error;
	}

	buf = usb_alloc_coherent(dev->udev, writesize, GFP_KERNEL,
				 &urb->transfer_dma);
	if (!buf) {
		retval = -ENOMEM;
		goto error;
	}

	if (copy_from_user(buf, user_buffer, writesize)) {
		retval = -EFAULT;
		goto error;
	}

	/* this lock makes sure we don't submit URBs to gone devices */
	mutex_lock(&dev->io_mutex);
	if (!dev->interface) {		/* disconnect() was called */
		mutex_unlock(&dev->io_mutex);
		retval = -ENODEV;
		goto error;
	}

	/* initialize the urb properly */
	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, dev->bulk_out_endpointAddr),
			  buf, writesize, U4all_write_bulk_callback, dev);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &dev->submitted);

	/* send the data out the bulk port */
	retval = usb_submit_urb(urb, GFP_KERNEL);
	mutex_unlock(&dev->io_mutex);
	if (retval) {
		err("%s - failed submitting write urb, error %d", __func__,
		    retval);
		goto error_unanchor;
	}

	/*
	 * release our reference to this urb, the USB core will eventually free
	 * it entirely
	 */
	usb_free_urb(urb);


	return writesize;


        case ISO:{
         	unsigned int pipe = usb_sndisocpipe (dev->udev, dev->out_endpointAddr);
         	int packetSize = usb_maxpacket (dev->udev, pipe, usb_pipeout (pipe));
        	int packets, lastPacketSize;
//        	unsigned int read_pipe = usb_rcvisocpipe (dev->udev, dev->in_endpointAddr);

        	//RESETEO PIPE DE LECTURA
//            usb_clear_halt(dev->udev,read_pipe);
  //          usb_clear_halt(dev->udev,pipe);
        	//FIN RESETEO PIPE DE LECTURA

//     		err("%s - packet size write %d", __FUNCTION__,packetSize);
             nurbs = writesize/dev->urbBufferSize;
             if(writesize % dev->urbBufferSize != 0)
                nurbs++;
//     		err("%s - nurbs %d", __FUNCTION__,nurbs);

             rem = writesize;
             for(i=0; i < nurbs; i++){
                curr_count = min(rem, dev->urbBufferSize);
                packets = curr_count/packetSize;
                lastPacketSize = curr_count%packetSize;                     
                if(lastPacketSize > 0)
                    packets++;
//     		err("%s - packets %d", __FUNCTION__,packets);
            	/* limit the number of URBs in flight to stop a user from using up all RAM */
            	if(down_interruptible(&dev->limit_sem)) {
            		retval = -ERESTARTSYS;
            		goto exit;
            	}

            	/* create a urb, and a buffer for it, and copy the data to the urb */
            	urb = usb_alloc_urb(0, GFP_KERNEL);
            	if(!urb) {
            		retval = -ENOMEM;
            		goto error;
            	}
            
            	buf = usb_buffer_alloc(dev->udev, curr_count, GFP_KERNEL, &urb->transfer_dma);
            	if (!buf) {
            		retval = -ENOMEM;
            		goto error;
            	}
        
            	if (copy_from_user(buf, user_buffer, curr_count)) {
            		retval = -EFAULT;
            		goto error;
            	}
            
            	/* initialize the urb properly */
                urb->transfer_buffer_length = curr_count;
                urb->number_of_packets = packets;
                urb->complete = U4all_write_iso_callback;
                urb->context = dev;
                urb->dev = dev->udev;
                urb->pipe = pipe;
                urb->transfer_flags = URB_ISO_ASAP| URB_NO_TRANSFER_DMA_MAP;
            	if (dev->udev->speed == USB_SPEED_HIGH)
            		urb->interval = 1 << (interval - 1);
            	else
            		urb->interval = interval;
            	//err("INTERVAL: %d",urb->interval);	
            	urb->start_frame = -1;
        
                for(i = 0; i < packets-1; i++){
                    urb->iso_frame_desc[i].offset = i * packetSize;
                    urb->iso_frame_desc[i].length = packetSize;
                }
                urb->iso_frame_desc[i].offset = i * packetSize;
                if(lastPacketSize > 0){
                    urb->iso_frame_desc[i].length = lastPacketSize;
                }else{
                    urb->iso_frame_desc[i].length = packetSize;
                }
                
/*                for(i=0;i < packets;i++)
            		//err("offset: %d  lenth: %d\n", urb->iso_frame_desc[i].offset , urb->iso_frame_desc[i].length );
 */       
            	/* send the data out the iso port */
            	retval = usb_submit_urb(urb, GFP_KERNEL);
            	if (retval) {
            		//err("%s - failed submitting write urb, error %d", __FUNCTION__, retval);
                    switch(retval){
                    	case -ENOMEM: err("error: ENOMEM\n");break;
                    	case -ENODEV: err("error: ENODEV\n");break;
                    	case -ENOENT: err("error: ENOENT\n");break;
                    	case -ENXIO: err("error: ENXIO\n");break;
                    	case -EINVAL: err("error: EINVAL\n");break;
                    	case -EAGAIN: err("error: EAGAIN\n");break;
                    	case -EFBIG: err("error: EFBIG\n");break;
                    	case -EPIPE: err("error: EPIPE\n");break;
                    	case -EMSGSIZE: err("error: EMSGSIZE\n");break;
                    	case -ESHUTDOWN: err("error: ESHUTDOWN\n");break;
                    	case -EPERM: err("error: EPERM\n");break;
                    	case -EHOSTUNREACH: err("error: EHOSTUNREACH\n");break;
                    }        
            		goto error;
            	}
               
            	/* release our reference to this urb, the USB core will eventually free it entirely */
            	usb_free_urb(urb);
            	rem -= curr_count;
             }   
        }
             
    }

error_unanchor:
	usb_unanchor_urb(urb);
error:
	if (urb) {
		usb_free_coherent(dev->udev, writesize, buf, urb->transfer_dma);
		usb_free_urb(urb);
	}
	up(&dev->limit_sem);

exit:
	return retval;
}

static int usb4all_ioctl(struct inode *inode, struct file *file, unsigned int code, unsigned long user_data){
        struct usb_U4all *u4alldev;
	struct usb_device* dev;
	int ret;
	struct usb_device_descriptor* descriptor; 
        u4alldev = (struct usb_U4all *)file->private_data;
        if (u4alldev == NULL)
                return -ENODEV;
	dev = u4alldev->udev;
	switch (code) {
	case SET_DESC_INDEX: {
		ret = get_user(descindex, (unsigned char*)user_data);
		return ret;
		break;
	}
        case SET_TIMEOUT: {
                ret = get_user(timeout, (unsigned char*)user_data);
                return ret;
                break;
        }
	case SET_TRANSFER_TYPE: {
                ret = get_user(transferType, (const char*)user_data);
                return ret;
                break;
        }
	case SET_IN_ENDPOINT: {
		ret = get_user(u4alldev->in_endpointAddr, (unsigned char*)user_data);
		u4alldev->in_size = endpointSizes[descindex].wMaxPacketSize;
		return ret;
		break;
	}
	case SET_OUT_ENDPOINT: {
		ret = get_user(u4alldev->out_endpointAddr, (unsigned char*)user_data);
		return ret;
		break;
	}
	case GET_STRING_DESCRIPTOR: {
	        struct usb_string_descriptor StringDesc;
        	struct usb_string_descriptor *pStringDesc;
        	dbg("%s - USB String ID = %d", __FUNCTION__, Id );

        	if (!usb_get_descriptor(dev, USB_DT_STRING, descindex, &StringDesc, sizeof(StringDesc))) {
               		return 0;
        	}

        	pStringDesc = kmalloc (StringDesc.bLength, GFP_KERNEL);

        	if (!pStringDesc) {
                	return 0;
        	}

        	if (!usb_get_descriptor(dev, USB_DT_STRING, descindex, pStringDesc, StringDesc.bLength )) {
                	kfree(pStringDesc);
                	return 0;
        	}

        	//unicode_to_ascii(string,  pStringDesc->wData,     pStringDesc->bLength/2-1);
		ret = copy_to_user((unsigned int __user *) user_data, pStringDesc, sizeof(*pStringDesc));
		//ret = copy_to_user((unsigned int __user *) user_data, string, strlen(string)+1);
        	kfree(pStringDesc);
        	return ret;
		break;
	}
	case DEBUG_STRING_DESCRIPTOR: {
	        struct usb_string_descriptor StringDesc;
                struct usb_string_descriptor *pStringDesc;
                char* string;
                dbg("%s - USB String ID = %d", __FUNCTION__, Id );

                if (!usb_get_descriptor(dev, USB_DT_STRING, descindex, &StringDesc, sizeof(StringDesc))) {
                        return 0;
                }

                pStringDesc = kmalloc (StringDesc.bLength, GFP_KERNEL);

                if (!pStringDesc) {
                        return 0;
                }

                if (!usb_get_descriptor(dev, USB_DT_STRING, descindex, pStringDesc, StringDesc.bLength )) {
                        kfree(pStringDesc);
                        return 0;
                }
		string = kmalloc (StringDesc.bLength, GFP_KERNEL);
		unicode_to_ascii(string,  pStringDesc->wData,     pStringDesc->bLength/2-1);
		ret = copy_to_user((unsigned int __user *) user_data, string, strlen(string)+1);
                kfree(pStringDesc);
                return ret;
                break;
	}	
	case GET_DEVICE_DESCRIPTOR: {
 		descriptor = kmalloc(sizeof *descriptor, GFP_NOIO);
		ret = usb_get_descriptor(dev, USB_DT_DEVICE, descindex, descriptor, USB_DT_DEVICE_SIZE);
		if (ret < 0) {
		    kfree(descriptor);
		    return ret;
	        }
		ret = copy_to_user((unsigned int __user *) user_data, descriptor, sizeof(*descriptor)); 
		return ret;
		break;
	}
	case GET_ENDPOINT_DESCRIPTOR: {
                struct usb_interface *interface;
                struct usb_host_interface *iface_desc;
                struct usb_endpoint_descriptor *endpoint;
                struct endpointSizeItem item;
		int subminor;
                subminor = iminor(inode);
                interface = usb_find_interface(&U4all_driver, subminor);
                endpoint = kmalloc(USB_DT_ENDPOINT_SIZE, GFP_NOIO);//TODO preguntar andres pq esa memoria
		if (!interface) {
                        dbg ("%s - error, can't find device for minor %d",
                        __FUNCTION__, subminor);
                        ret = -ENODEV;
                        return ret;
                }
                iface_desc = interface->cur_altsetting;
		endpoint = &iface_desc->endpoint[descindex].desc;
              	item.bEndpointAddress = endpoint->bEndpointAddress;
		item.wMaxPacketSize = endpoint->wMaxPacketSize; 
		endpointSizes[descindex] = item;
		ret = copy_to_user((unsigned int __user *) user_data, endpoint, USB_DT_ENDPOINT_SIZE);
                return ret;
                break;
	}
	case GET_INTERFACE_DESCRIPTOR: {
		struct usb_interface *interface;
		struct usb_host_interface *iface_desc;
        	int subminor;
		subminor = iminor(inode);
		iface_desc = kmalloc(USB_DT_INTERFACE_SIZE, GFP_NOIO);
		interface = usb_find_interface(&U4all_driver, subminor);
        	if (!interface) {
                	dbg ("%s - error, can't find device for minor %d",
                   	__FUNCTION__, subminor);
                	ret = -ENODEV;
                	return ret;
        	}
		iface_desc = interface->cur_altsetting;
                ret = copy_to_user((unsigned int __user *) user_data, iface_desc, USB_DT_INTERFACE_SIZE);
                return ret;
                break;
        }
	case GET_CONFIGURATION_DESCRIPTOR: {
		struct usb_config_descriptor* config;
		config = kmalloc(USB_DT_CONFIG_SIZE, GFP_NOIO);
		//unsigned char bufereo[255];
		//ret =  usb_get_descriptor(dev, USB_DT_CONFIG, descindex, bufereo, 256);
		ret =  usb_get_descriptor(dev, USB_DT_CONFIG, descindex, config, USB_DT_CONFIG_SIZE);
	        if (ret < 0) {
                    return ret;
                }
                ret = copy_to_user((unsigned int __user *) user_data, config, USB_DT_CONFIG_SIZE);
                return ret;
                break;
	}
	default:
		return -ENOSYS;
	}
}



static const struct file_operations U4all_fops = {
	.owner =	THIS_MODULE,
	.read =		U4all_read,
	.write =	U4all_write,
	.open =		U4all_open,
	.release =	U4all_release,
	.flush =	U4all_flush,
	.llseek =static struct usb_device_id USB4all_table	U4all_llseek,
};

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver U4all_class = {
	.name =		"usb4all%d",
	.fops =		&U4all_fops,
	.minor_base =	USB4all_MINOR_BASE,
};

static int U4all_probe(struct usb_interface *interface,
		      const struct usb_device_id *id)
{
	struct usb_U4all *dev = NULL;
	//size_t buffer_size;
	//int i;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		err("Out of memory");
		goto error;
	}
	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	dev->in_size = 0x0040;
    dev->urbBufferSize = 60;	//TODO
    dev->nurbs = 10;	//TODO
    INIT_LIST_HEAD(&dev->free_read_urbs);
    INIT_LIST_HEAD(&dev->busy_read_urbs);
    init_waitqueue_head(&dev->read_wait);

    
	/* set up the endpoint information */
	/* use only the first bulk-in and bulk-out endpoints */
	/*iface_desc = interface->cur_altsetting;
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!dev->bulk_in_endpointAddr &&
		    ((endpoint->bEndpointAddress & USB_ENDPOINT_DIR_MASK)
					== USB_DIR_IN) &&
		    ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)
					== USB_ENDPOINT_XFER_BULK)) {*/
			/* we found a bulk in endpoint */
	/*		buffer_size = usb_endpoint_maxp(endpoint);
			dev->bulk_in_size = buffer_size;
			dev->bulk_in_endpointAddr = endpoint->bEndpointAddress;*/
			dev->in_buffer = kmalloc(0x0040/*buffer_size*/, GFP_KERNEL);
			if (!dev->in_buffer) {
				err("Could not allocate bulk_in_buffer");
				goto error;
			}/*
		}

		if (!dev->bulk_out_endpointAddr &&
		    ((endpoint->bEndpointAddress & USB_ENDPOINT_DIR_MASK)
					== USB_DIR_OUT) &&
		    ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)
					== USB_ENDPOINT_XFER_BULK)) {*/
			/* we found a bulk out endpoint */
	/*		dev->bulk_out_endpointAddr = endpoint->bEndpointAddress;
		}
	}
	if (!(dev->bulk_in_endpointAddr && dev->bulk_out_endpointAddr)) {
		err("Could not find both bulk-in and bulk-out endpoints");
		goto error;
	}*/

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &U4all_class);
	if (retval) {
		/* something prevented us from registering this driver */
		err("Not able to get a minor for this device.");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	/* let the user know what node this device is now attached to */
	info("USB4all device now attached to usb4all-%d", interface->minor);
	return 0;

error:
	if (dev)
		kref_put(&dev->kref, U4all_delete);
	return retval;
}

static void U4all_disconnect(struct usb_interface *interface)
{
	struct usb_skel *dev;
	int minor = interface->minor;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	/* give back our minor */
	usb_deregister_dev(interface, &U4all_class);

	/* prevent more I/O from starting */
	mutex_lock(&dev->io_mutex);
	dev->interface = NULL;
	mutex_unlock(&dev->io_mutex);

	usb_kill_anchored_urbs(&dev->submitted);

	/* decrement our usage count */
	kref_put(&dev->kref, U4all_delete);

	dev_info(&interface->dev, "USB4all #%d now disconnected", minor);
}

static void U4all_draw_down(struct usb_U4all *dev)
{
	int time;

	time = usb_wait_anchor_empty_timeout(&dev->submitted, 1000);
	if (!time)
		usb_kill_anchored_urbs(&dev->submitted);
	usb_kill_urb(dev->bulk_in_urb);
}

static int U4all_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usb_U4all *dev = usb_get_intfdata(intf);

	if (!dev)
		return 0;
	U4all_draw_down(dev);
	return 0;
}

static int U4all_resume(struct usb_interface *intf)
{
	return 0;
}

static int U4all_pre_reset(struct usb_interface *intf)
{
	struct usb_U4all *dev = usb_get_intfdata(intf);

	mutex_lock(&dev->io_mutex);
	U4all_draw_down(dev);

	return 0;
}

static int skel_post_reset(struct usb_interface *intf)
{
	struct usb_skel *dev = usb_get_intfdata(intf);

	/* we are sure no URBs are active - no locking needed */
	dev->errors = -EPIPE;
	mutex_unlock(&dev->io_mutex);

	return 0;
}

static struct usb_driver U4all_driver = {
	.name =		"USB4all baseboard",
	.probe =	U4all_probe,
	.disconnect =	U4all_disconnect,
	.suspend =	U4all_suspend,
	.resume =	U4all_resume,
	.pre_reset =	U4all_pre_reset,
	.post_reset =	U4all_post_reset,
	.id_table =	U4all_table,
	.supports_autosuspend = 0,
};

static int __init usb_U4all_init(void)
{
	int result;

	/* register this driver with the USB subsystem */
	result = usb_register(&U4all_driver);
	if (result)
		err("usb_register failed. Error number %d", result);

	return result;
}

static void __exit usb_U4all_exit(void)
{
	/* deregister this driver with the USB subsystem */
	usb_deregister(&U4all_driver);
}

/******************************************************************************
 * unicode_to_ascii extracted from io_edgeport.c			      *		
 *	Turns a string from Unicode into ASCII.                               *
 *      Doesn't do a good job with any characters that are outside the normal *
 *      ASCII range, but it's only for debugging...                           *
 *      NOTE: expects the unicode in LE format				      *						
 *****************************************************************************/

static void unicode_to_ascii (char *string, __le16 *unicode, int unicode_size)
{
        int i;

        if (unicode_size <= 0)
                return;

        for (i = 0; i < unicode_size; ++i)
                string[i] = (char)(le16_to_cpu(unicode[i]));
        string[unicode_size] = 0x00;
}

module_init(usb_U4all_init);
module_exit(usb_U4all_exit);

MODULE_LICENSE("GPL");
