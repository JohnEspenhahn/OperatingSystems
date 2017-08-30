#include <stdlib.h>
#include <assert.h>

typedef struct _LinkedList {
  void* value;
  struct _LinkedList* next;
} LinkedList;

LinkedList* create_linkedlist(void* value) {
  LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
  assert(ll != NULL);

  ll->value = value;
  ll->next = NULL;

  return ll;
}