#include <xinu.h>

extern syscall regcallback(int32 (*fp)(void));
extern int32 mycallback(void);

process receivetest(void){

	if(regcallback(&mycallback) != OK){
		kprintf("registration failed");
		return 1;
	}
	kprintf("into receive\n");

	while(TRUE){

		sleepms(5000);
		kprintf("the message received is %s\n", messagers);
		
	}
    return OK;
}