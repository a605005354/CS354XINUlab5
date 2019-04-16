#include <xinu.h>

process sendtest(pid32 pid, umsg32 msg){
    /*kprintf("send pid is");
    kprintf("%d",pid);
    kprintf("\n");*/
    //`kprintf("into send\n");
    send(pid,msg);
}
