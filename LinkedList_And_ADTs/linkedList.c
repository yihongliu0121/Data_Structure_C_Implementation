#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>


struct Link* insert(struct Link* sorted, struct Link* position, struct Link* new_Item){
    //check if added to the beginning
    //printf( "lined in %d\n", position->value);
    //printf( "sorted in %d\n\n", sorted->value);
    
    if(sorted == position) {
        new_Item->next = sorted;
        //printf("****** equal *****\n");
        return new_Item;
    }
    
    struct Link* pom = sorted;
    while(pom->next != position) {
        pom = pom->next;
    }
    
    new_Item->next = pom->next;
    pom->next = new_Item;
    
    return sorted;
    
}

struct Link* listInsertionSort(struct Link* head) {
    
    /*
     * This function should perform an insertion sort on the list whose head is
     * provided as the function's argument, so that the values in the list are
     * sorted in ascending order, starting at the head.
     *
     * The sort should be done without allocating any new Link structs or any
     * other auxiliary data structures.
     *
     * Return a pointer to the new head of the list.
     */
    
    struct Link* sorted = head;
    struct Link* current = head;
    struct Link* pos;         //match position
    struct Link* temp;
    int i = 0;
    
    
    while(current->next != NULL) {
        
        //printf( "\n\nThe %d floor \n", i);

        pos = sorted;       //reset position
        int j = 0;
        while( current->next != NULL && pos->value < current->next->value){
            //printf(" %d : %d \n", i, j);
            pos = pos->next;
            j++;
        }
        //printf( "lined %d\n", pos->value);
        
        if(current->next != pos) {          //element moves
            //printf("Get into\n");
            temp = current->next;
            current->next = current->next->next;    //go to next
            sorted = insert(sorted, pos, temp);
        }
        else{
            current = current->next;
        }

        i++;
    }
    
    head = sorted;
    return head;
    
}


struct Link* reverseList(struct Link* head) {
    
    /*
     * This function should iteratively reverse the list whose head is provided
     * as the function's argument.
     *
     * The reversal must be done totally in place, i.e. you may not allocate any
     * new Link structs or any other auxiliary data structures.
     *
     * Return a pointer to the new head of the list.
     */
    
    struct Link* prev = NULL;
    struct Link* current = head;
    struct Link* next;
    
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    
    return head;
    
}



struct Link* reverseListRecursive(struct Link* head){
    
    /*
     * Write this function for extra credit.  It should do the exact same thing
     * as reverseList() above, except it should do it recursively instead of
     * iteratively (i.e. no loops allowed).
     *
     * Again, you may not allocate any new Link structs or any other auxiliary
     * data structures.  You may, however, define an auxiliary function to help
     * you do the recursion.
     *
     * Return a pointer to the new head of the list.
     */
    
    if(head == NULL)    //reverse null
        return NULL;
    
    if(head->next == NULL)  //single element
        return head;
    struct Link* rec = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    
    head = rec;
    return head;
    
}
