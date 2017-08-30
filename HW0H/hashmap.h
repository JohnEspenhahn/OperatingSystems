#include <stdbool.h>
#include <stdlib.h>
#include "linkedlist.h"

typedef struct {
  // Array of LinkedList<HashMapEntry>
  LinkedList** buckets;
  // Length of buckets
  size_t length;
} HashMap;

typedef struct {
  int key;
  void* value;
} HashMapEntry;

HashMap* create_hashmap_int(size_t length) {
  HashMap* m = malloc(sizeof(HashMap));
  assert(m != NULL);

  m->length = length;
  m->buckets = calloc(sizeof(LinkedList*) * length, sizeof(LinkedList*));
  assert(m->buckets != NULL);

  return m;
}

static inline LinkedList** hashmap_get_bucket(HashMap* m, int key) {
  const int idx = key % m->length;
  return &m->buckets[idx];
}

void* hashmap_get(HashMap* m, int key) {
  assert(m != NULL);

  LinkedList* ll = *hashmap_get_bucket(m, key);
  while (ll != NULL) {
    // Get value at first index in LinkedList
    HashMapEntry* entry = (HashMapEntry*) ll->value;
    // Get key from entry and check for match
    if (entry->key == key)
      return entry->value;
    else
      ll = ll->next;
  }

  return NULL;
}

static HashMapEntry* create_hashmap_entry(int key, void* value) {
  HashMapEntry* e = malloc(sizeof(HashMapEntry));
  assert(e != NULL);

  e->key = key;
  e->value = value;

  return e;
}

void hashmap_put(HashMap* m, int key, void* value) {
  assert(m != NULL);

  LinkedList** ll_pointer = hashmap_get_bucket(m, key);
  if (*ll_pointer == NULL) {
    // Bucket is empty, init
    *ll_pointer = create_linkedlist(create_hashmap_entry(key, value));
  } else {
    // Move to end
    LinkedList* ll = *ll_pointer;
    while (ll->next != NULL) {
      ll = ll->next;
    }

    // Make next
    ll->next = create_linkedlist(create_hashmap_entry(key, value));
  }
}