#include <xinu.h>

extern int text;
extern int etext;
syscall regcallback(int32 (*fp)(void)){
    intmask mask;
	mask = disable();
    struct	procent *prptr;

    /*if(fp < &text || fp > &etext || fp == NULL){
        restore(mask);
        return  SYSERR;
    }*/

    //kprintf("into regcallback\n");
    prptr = &proctab[currpid];
    prptr->prcbreg = TRUE;
    prptr->fcb = fp;

    restore(mask);
    return OK;
}
