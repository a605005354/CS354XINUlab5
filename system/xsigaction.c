#include <xinu.h>


syscall xsigaction(
    uint16 sigtype, 
    int32 (* fp)(void), 
    uint32 optarg
    )
    {

    intmask mask;
	mask = disable();
    
    struct	procent *prptr;

    if(sigtype == 3){

    }
    else if(sigtype == 4){

    }
    else if(sigtype == 5){
        
    }
 //   kprintf("into regcallback\n");
 

    restore(mask);
    return OK;
}
