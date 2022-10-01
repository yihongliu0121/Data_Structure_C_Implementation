#include <stdio.h>
#include <assert.h>
#include "linkedListQueue.h"

#define NUM_TEST_VALUES 16

int main() {

  struct ListQueue* queue = createListQueue();
  TYPE values[NUM_TEST_VALUES];

  for (int i = 0; i < NUM_TEST_VALUES; i++) {
    values[i] = i;
    addBackListQueue(queue, i);
  }

  printf("\nChecking queue ordering...\n");
  for (int i = 0; i < NUM_TEST_VALUES; i++) {
    assert(frontListQueue(queue) == values[i]);
    removeFrontListQueue(queue);
  }
  printf("  ... queue is good!\n");

}
