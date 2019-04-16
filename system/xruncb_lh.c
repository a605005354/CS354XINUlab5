#include <xinu.h>


extern unsigned int case2;
void xruncb_lh(void){
    struct procent * recproc = &proctab[currpid];
    asm("movl %0, 4(%%ebp)\n\t"
            :
            : "r"(case2)
            : );
     int (*funcPt)() = recproc->fcb;
    (* funcPt)();          
}

/*extern syscall stacktrace(int pid);

void    xruncb_lh(void){
    kprintf("into xruncb_lh\n");
    mycallback();
    struct	procent *prptr = &proctab[currpid];
    //kprintf("current pid is %d\n",currpid);
    unsigned int* ret;
    asm("movl %%ebp, %0\n\t"
        :"=r"(ret)
        :
        :
    );

    stacktrace(currpid);
    kprintf("the adr of ptr in cb is 0x%X\n",ret);
    ret += 1;
    kprintf("the content of saveptr in cb is %d\n", *savedptr2);
    *ret = *savedptr2;
    kprintf("the adr of ptr afterrrrr in cb is 0x%X\n",ret);
    return;
}*/