#include <xinu.h>

extern unsigned int case1;
void xruncb_uh(void){
                struct procent * recproc = &proctab[currpid];
                asm("movl %0, 4(%%ebp)\n\t"
                                :
                                : "r"(case1)
                                : );
                int (*funcPt)() = recproc->fcb;
                (* funcPt)();
}



/*extern syscall stacktrace(int pid);

void    xruncb_uh(void){
    //kprintf("into xruncb_uh\n");
    mycallback();
    struct	procent *prptr = &proctab[currpid];
    //kprintf("current pid is %d\n",currpid);
    unsigned int* ret;
    asm("movl %%ebp, %0\n\t"
        :"=r"(ret)
        :
        :
    );

    //stacktrace(currpid);
    //kprintf("the content of saveptr in cb is %d\n",*savedptr);
    //kprintf("the adr of ptr in cb is 0x%X\n",ret);
    ret+=1;
    *ret = *savedptr;
    //kprintf("the adr of ptr afterrrrr in cb is 0x%X\n",ret);
    return;
}*/
