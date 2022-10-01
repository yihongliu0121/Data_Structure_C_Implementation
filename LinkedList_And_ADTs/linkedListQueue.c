#include "linkedListQueue.h"
#include "assert.h"
#include <stdlib.h>



struct Link {
	TYPE          val;
	struct Link *next;
};


/* Singly Linked List with Head and Tail */
struct ListQueue {
   struct Link *head;
   struct Link *tail;
};



/* List queue with a sentinel at the front */

void initListQueue (struct ListQueue *q) {
/* FIXME: You will have to write this */
    struct Link *sentinel=(struct Link*)malloc(sizeof(struct Link));
    assert(sentinel!=0);
    sentinel->next=0;
    q->head=q->tail=sentinel;
}




struct ListQueue *createListQueue()
{
	struct ListQueue *newList = malloc(sizeof(struct ListQueue));
	initListQueue(newList);
	return newList;
}

void _freeListQueue(struct ListQueue *l) {
  while (!isEmptyListQueue(l))
  {
     removeFrontListQueue(l);
  }
}

void deleteListQueue(struct ListQueue *l)
{
	_freeListQueue(l);
	free(l);
	l = 0;
}



void addBackListQueue (struct ListQueue *q, TYPE val) {
/* FIXME: You will have to write this */
    struct Link* lnk=(struct Link*)malloc(sizeof(struct Link));
    assert(lnk!=0);
    lnk->value=val;
    q->tail->next=lnk;
    q-tail=link;
}


TYPE frontListQueue (struct ListQueue *q) {
/* FIXME: You will have to write this */
    return q->head->next->val;
}


void removeFrontListQueue (struct ListQueue *q) {
/* FIXME: You will have to write this */
    struct Link* lnk=q->head->next;
    assert(! isEmptyListQueue(q));
    q->head->next=lnk->next;
    if (q->head->next==0)
        q->tail=q->head;
    free(lnk);
}

int isEmptyListQueue (struct ListQueue *q) {
/* FIXME: You will have to write this*/
    return q->head==q->tail;
}

