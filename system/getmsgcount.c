#include <xinu.h>

uint32 getmsgcount(void){
    uint32 count;
    struct	procent *prptr;	
    prptr = &proctab[currpid];
    count = prptr->prmsgcount;
    return count;
}