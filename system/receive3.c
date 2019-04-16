/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive3(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	/*if(prptr->prmqhead != NULL){
		struct msgqueue *node;
		node = prptr->prmqhead;
		kprintf("queuelist: ");
		while(node != NULL){
			kprintf(node->mqmsg);
			node = node->mqnext;
		}
			kprintf("\n");
	}*/

	if (prptr->prmsgcount == 0) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	/*msg = prptr->prmsg;*/		/* Retrieve message		*/
	/*prptr->prhasmsg = FALSE;*/	/* Reset message flag		*/
	msg = mqextract();

	restore(mask);
	return msg;
}

