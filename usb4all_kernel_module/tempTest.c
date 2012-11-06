#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <usb.h>
//#include <sys/ioctl.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_REQ_LEN 20

/* IOCTL commands */
#define GET_DEVICE_DESCRIPTOR           0x0001
#define SET_DESC_INDEX                  0x0002
#define SET_IN_ENDPOINT                 0x0003
#define SET_OUT_ENDPOINT                0x0004
#define GET_ENDPOINT_DESCRIPTOR         0x0005
#define GET_INTERFACE_DESCRIPTOR        0x0006
#define GET_CONFIGURATION_DESCRIPTOR    0x0007
#define SET_TRANSFER_TYPE               0x0008
#define SET_TIMEOUT                     0x0009
#define GET_STRING_DESCRIPTOR           0x000a
#define DEBUG_STRING_DESCRIPTOR         0x000b

#define CTRL	0
#define INT	1
#define BULK	2
#define ISO	3


main(int argc, char **argv){
    struct usb_endpoint_descriptor edescriptor; 
    int fd, ret, i, in_bulk_endpoint_addr, out_bulk_endpoint_addr;
    int in_iso_endpoint_addr, out_iso_endpoint_addr;
    unsigned int handler;
    char question[MAX_REQ_LEN];
    char answer[MAX_REQ_LEN];
    int rawval,rawtemp;
    float degCtemp;

    fd  = open("/dev/usb4all0", O_RDWR, 0);
    if(fd > 0){
        i = BULK;
        ret = ioctl(fd, SET_TRANSFER_TYPE, (&i));

        //OBTENGO ENDPOINT ADDRESSES
        //IN ENDPOINTS	
        i = 1;//bulk
        ret = ioctl(fd, SET_DESC_INDEX, (&i));
        if(ret){
          perror("Fallo SET_DESC_INDEX");
          exit(1);
        }
        ret = ioctl(fd, GET_ENDPOINT_DESCRIPTOR, (&edescriptor));
        in_bulk_endpoint_addr = edescriptor.bEndpointAddress;

        i=5;//iso
        ret = ioctl(fd, SET_DESC_INDEX, (&i));
        if(ret){
          perror("Fallo SET_DESC_INDEX");
          exit(1);
        }
        ret = ioctl(fd, GET_ENDPOINT_DESCRIPTOR, (&edescriptor));
        in_iso_endpoint_addr = edescriptor.bEndpointAddress;

        //OUT ENDPOINTS
    	i=0;//bulk
        ret = ioctl(fd, SET_DESC_INDEX, (&i));
        if(ret){
          perror("Fallo SET_DESC_INDEX");
          exit(1);
        }
        ret = ioctl(fd, GET_ENDPOINT_DESCRIPTOR, (&edescriptor));
        out_bulk_endpoint_addr = edescriptor.bEndpointAddress;	
    	i=4;//iso 
        ret = ioctl(fd, SET_DESC_INDEX, (&i));
        if(ret){
          perror("Fallo SET_DESC_INDEX");
          exit(1);
        }
        ret = ioctl(fd, GET_ENDPOINT_DESCRIPTOR, (&edescriptor));
        out_iso_endpoint_addr = edescriptor.bEndpointAddress;	

        //SETEO ENDPOINTS PARA OPEN
        
        ret = ioctl(fd, SET_IN_ENDPOINT, &in_bulk_endpoint_addr);
        if(ret){
          perror("Fallo SET_IN_ENDPOINT");
          exit(1);
        }

        ret = ioctl(fd, SET_OUT_ENDPOINT, &out_bulk_endpoint_addr);
        if(ret){
          perror("Fallo SET_OUT_ENDPOINT");
          exit(1);
        }


        //envio comando para abrir el modulo de temperatura
        question[0] = (char)0x00;            //HEADER
        question[1] = (char)0x04;            //HEADER
        question[2] = (char)0x00;            //HEADER

        question[3] = (char)0x00;//open
        question[4] = (char)0x03;//IN_EP
        question[5] = (char)0x03;//OUT_EP
        question[6] = (char)'t';
        question[7] = (char)'e';
        question[8] = (char)'m';
        question[9] = (char)'p';
        question[10] = (char)'\0';

        ret = write(fd,question,11);
//        printf("paso write1: %d\n", ret);
        if(ret < 0){
            perror("Fallo write load module");
        }else{
            ret = read(fd,answer,5);  
//            printf("paso read1: %d\n",ret);
            if(ret < 0)  
                perror("Fallo read handler");
            else{
                handler = answer[4];
/*
                for(i = 0;i < 5;i++){
                   printf("answer[%d] = %d\n",i,answer[i]);
                }
*/
//                printf("HANDLER: %d\n",handler);

                //SETEO ENDPOINTS PARA MODULO TEMP
                i = ISO;
                ret = ioctl(fd, SET_TRANSFER_TYPE, (&i));

                ret = ioctl(fd, SET_IN_ENDPOINT, &in_iso_endpoint_addr);
                if(ret){
                  perror("Fallo SET_IN_ENDPOINT");
                  exit(1);
                }
        
                ret = ioctl(fd, SET_OUT_ENDPOINT, &out_iso_endpoint_addr);
                if(ret){
                  perror("Fallo SET_OUT_ENDPOINT");
                  exit(1);
                }


                 
                //envio pedido de lectura de la temperatura
//                question[0] = (char)(handler<<3);        //HEADER
                question[0] = (char)0x08;        //HEADER(handler)
                question[1] = (char)0x00;            //HEADER
                question[2] = (char)0x00;            //HEADER
        
                question[3] = (char)0x34;
                question[4] = (char)0x02;
                ret = write(fd,question,5);
//                printf("paso write2: %d\n", ret);
                if(ret < 0){
                  perror("Fallo write cmd read temp");
                }else{
                    ret = read(fd,answer,6);  
//                    printf("paso read2: %d\n", ret);
                    if(ret < 0){
                      perror("Fallo read temp");
                    }else{
                        rawval = answer[4] + (answer[5]<<8);
                
                        if( rawval & (1 << 15) )
                             rawval -= 1 << 16;
                
                        rawtemp = (rawval)>>3;
                        degCtemp = rawtemp * 0.0625;
                        printf("The temperature is %f degC (raw: %i, rawval: %i)\n", degCtemp, rawtemp, rawval); 
                    }
                }
            }  
            //CLOSE MODULO TEMP
            //TODO
        }
        close(fd);
    }else
        perror("Fallo Open");
}


