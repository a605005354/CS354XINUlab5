#include <xinu.h>

extern syscall send3(pid32, umsg32);
extern umsg32 receive3(void);
extern uint32 getmsgcount(void);
uint32 flag = 0;
uint32 flag2 = 0;
void receiver3() {
	intmask mask = disable();
	//kprintf("%d\n", getmsgcount());
	int count = getmsgcount();
	for (int i = 0; i < count; i++) {
		umsg32 msg= receive3();
		kprintf("Message received: %d\n", msg);
	}
	restore(mask);
}
void receiver3_bonus() {
	intmask mask = disable();
	//kprintf("%d\n", getmsgcount());
	for (int i = 0; i < 3; i++) {
		umsg32 msg= receive3();
		kprintf("Message received: %d\n", msg);
	}
	kprintf("Receiver freed %d bytes\n", memlist.mnext->mlength);
	restore(mask);
}
int32 testcallback(void) {
	umsg32 ubuffer = receive();
	intmask mask = disable();
	kprintf("Receiver pid: %d  Message received:%d\n",  currpid, ubuffer);
	restore(mask); 
	return OK;
}
void receiverPart4uh(void) {
	if (regcallback(&testcallback) != OK) {
		kprintf("registration failed\n");	
		return 1;
	}
	sleepms(100);
	kprintf("This should be printed after callback function\n\n");	
	sleepms(100);
	kprintf("This should be printed after callback function\n\n");
	kprintf("Epilogue of receiver reached\n");
}
void receiverPart4lh(void) {
	if (regcallback(&testcallback) != OK) {
		kprintf("registration failed\n");	
		return 1;
	}
	int x = 0;
	for (int i = 0; i < 30000000; i++) {
		x++;
		if (flag2 == 1) {
			kprintf("lower half: this should be printed after the receiver\n\n");
			flag2 = 0;
		}
	}
	kprintf("Epilogue of lower half receiver reached\n");
}
void nonBlockingSendPart4(pid32 receiverProcess, umsg32 msg){
	int32 val = send(receiverProcess, 10);
	flag = 1;
	if(val != OK) {
		kprintf("Could not send: %d\n", 10);
	}
}
void nonBlockingSendPart4_sleep(pid32 receiverProcess, umsg32 msg){
	sleepms(150);
	int32 val = send(receiverProcess, 20);
	flag = 1;
	if(val != OK) {
		kprintf("Could not send: %d\n", 20);
	}
}
process	main(void)
{

	 intmask mask = disable();
 	 /*pid32 re = create(receiver3, 1024, 20, "receiver3",0,NULL);
 	 for (int i = 1; i < 10; i++) {
 	 	syscall ok = send3(re, i);
 	 	if (ok == SYSERR) {
 	 		kprintf("The %d-th send fails\n", i);
 	 	}
 	 }
 	 restore(mask);

 	 resume(re);
 	 kill(re);

 	 uint32 initial_length = memlist.mnext->mlength;*/

	 //re = create(receiver3, 1024, 20, "receiver3",0,NULL);
	 //send3(re,200);

	 /*if (memlist.mnext->mlength == initial_length-8){
	 	send3(re,300);
	 	if (memlist.mnext->mlength == initial_length-16) {
	 		kprintf("Heap storage after send is correct.\n");
	 	} else {
	 		kprintf("Heap storage after send is wrong.\n");
	 	}
	 	
	 } else {
	 	kprintf("Heap storage after send is wrong.\n");
	 }*/

	 //resume(re);

	 /*if (memlist.mnext->mlength == initial_length){
	 	kprintf("Heap storage after receive is correct.\n");
	 } else {
	 	kprintf("Heap storage after receive is wrong.\n");
	 }*/

	kprintf("\n\n\n");
	kprintf("Test 3 Part 4 Upper Half\n\n");
		
	pid32 receiverProcessuh = create(receiverPart4uh, 1024, 20, "receiveruh", 0);

	resume(receiverProcessuh);
	kprintf("pid is %d\n", receiverProcessuh);
	resume(create(nonBlockingSendPart4, 1024, 20, "NBS1", 2, receiverProcessuh, 1));
	resume(create(nonBlockingSendPart4_sleep, 1024, 20, "NBS1", 2, receiverProcessuh, 1));

	sleepms(2000);

	kprintf("\n\n\n");
	flag = 0;
	kprintf("Test 3 Part 4 Lower Half\n\n");
	pid32 receiverProcesslh = create(receiverPart4lh, 1024, 20, "receiverlh", 0); 
	resume(receiverProcesslh);
	resume(create(nonBlockingSendPart4, 1024, 20, "NBS1", 2, receiverProcesslh, 1));
	resume(create(nonBlockingSendPart4_sleep, 1024, 20, "NBS1", 2, receiverProcesslh, 1));

	//12
	/*sleepms(2000);
	kprintf("\n\n\n");
	uint32 bonus_le = memlist.mnext->mlength;
	mask = disable();
 	pid32 re_bonus = create(receiver3_bonus, 1024, 20, "receiver3_bonus",0,NULL);
 	for (int i = 1; i < 8; i++) {
 		syscall ok = send3(re_bonus, i);
 	}
 	uint32 used = bonus_le-memlist.mnext->mlength;
 	kprintf("Senders used %d bytes\n",used);
 	restore(mask);
 	
 	resume(re_bonus);
 	sleepms(200);
 	kill(re_bonus);
 	if (memlist.mnext->mlength == bonus_le)
 		kprintf("Bonus correct\n");
 	else
 		kprintf("Bonus wrong\n");*/
}