#include <xinu.h>

struct msgqueue *mqinsert(umsg32 m, pid32 recvpid){
	intmask mask;
	mask = disable();
	kprintf("problem1\n");
	struct procent *prptr = &proctab[recvpid];
	struct msgqueue *node;

	kprintf(prptr->prmqhead->mqmsg);
	if(prptr->prmqhead == NULL){
		prptr->prmqhead = (struct msgqueue *)getmem(sizeof(struct msgqueue));
		prptr->prmqhead->mqnext = NULL;
		prptr->prmqhead->mqmsg = m;
		prptr->prmqtail = prptr->prmqhead;
	}
	else{
		kprintf("problem2\n");
		prptr->prmqtail->mqnext = (struct msgqueue *)getmem(sizeof(struct msgqueue));
		prptr->prmqtail->mqnext->mqmsg = m;
		prptr->prmqtail->mqnext->mqnext = NULL;
		prptr->prmqtail = prptr->prmqtail->mqnext;
		kprintf("problem3\n");
	}

	node = prptr->prmqhead;
	while(node != NULL){
		node = node->mqnext;
	}

	prptr->prmsgcount += 1;
	restore(mask);
	return node;
	/*prptr->prmsg = m;*/		/* Deliver message		*/
	/*prptr->prhasmsg = TRUE;*/		/* Indicate message is waiting	*/

}
