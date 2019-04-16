/* send.c - send */

#include <xinu.h>

extern syscall stacktrace(int pid);
extern void    xruncb_uh(void);
extern void    xruncb_lh(void);
/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/


	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}


	prptr->prmsg = msg;
	prptr->prhasmsg = TRUE;
	/*else if(prptr->prmsgcount > MAXIPC){
		restore(mask);
		return SYSERR;
	}*/
	/* If recipient waiting or in timed-wait make it ready */



		//int* ret;
	if (prptr->prcbreg){
        if(prptr->prstate==PR_SLEEP){
			//kprintf("Sleeping");
            unsigned int * stackReceive =(unsigned int *) prptr->prstkptr;
            stackReceive += 30;
            case1 = *stackReceive;
            *stackReceive = xruncb_uh;
            }
            else{
				//kprintf("Nonsleeping");
            	case2 = *(prptr->clkdispaddr); //global variable
                *(prptr->clkdispaddr) = xruncb_lh;
                }
    }

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
		/*if(prptr->prstate == PR_SLEEP){
			ret = prptr->prstkptr;
			//kprintf("the adr of ptr is 0x%X\n",ret);
			ret += 30;
			//kprintf("the adr of ptr after is 0x%X\n",ret);
			*savedptr = *ret;
			//kprintf("the content of saveptr is %d\n",*savedptr);
			*ret = &xruncb_uh;
		}*/
		/*else if(prptr->prstate == PR_READY){
			//kprintf("process is busy readying\n");
		}*/
		//stacktrace(pid);

	restore(mask);		/* Restore interrupts */
	return OK;
}

