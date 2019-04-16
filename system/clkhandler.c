/* clkhandler.c - clkhandler */

#include <xinu.h>

extern void    xruncb_lh(void);
/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	unsigned int* ret;
	//kprintf("the adr of ptr beforeeee in cb is 0x%X\n",ret);
    //kprintf("the adr of ptr afterrrr in cb is 0x%X\n",ret);

	struct	procent *prptr;
	prptr = &proctab[currpid];
	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		//stacktrace(currpid);
		preempt = QUANTUM;
		resched();
		if(prptr->prcbreg == TRUE ){
			asm("movl %%ebp,%0\n\t"
                :"=r"(prptr->clkdispaddr)
                :
                :
                );
            prptr->clkdispaddr = prptr->clkdispaddr+10;

			/*asm("movl %%ebp, %0\n\t"
        	:"=r"(ret)
        	:
        	:
   			 );
				ret += 10;
				*savedptr2 = *ret;
				//kprintf("the content of saveptr is %d\n",*savedptr2);
				*ret = &xruncb_lh;*/
		}

	}
}
