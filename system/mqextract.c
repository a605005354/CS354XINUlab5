#include <xinu.h>

umsg32  mqextract(void){
    intmask mask;
	mask = disable();
    umsg32 message;

    struct procent *prptr = &proctab[currpid];
    struct msgqueue *node;
    
    node = prptr->prmqhead;
    message = node->mqmsg;
    prptr->prmqhead = prptr->prmqhead->mqnext;
    freemem(node,sizeof(struct msgqueue));
    node->mqnext = NULL;
    node->mqmsg = NULL;

    prptr->prmsgcount -= 1;
    restore(mask);
    return message;
}