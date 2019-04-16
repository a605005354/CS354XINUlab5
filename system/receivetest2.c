#include <xinu.h>

extern syscall regcallback(int32 (*fp)(void));
extern int32 mycallback(void);

process receivetest2(void){

	if(regcallback(&mycallback) != OK){
		kprintf("registration failed");
		return 1;
	}
	kprintf("into receive2\n");

	while(TRUE){
		//kprintf("the message received is %s\n", messagers);
	}
    return OK;
}