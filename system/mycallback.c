#include <xinu.h>

int32 mycallback(void){
    
    messagers = receive();
    kprintf("The callback message received is %s\n", messagers);
    return(OK);
}