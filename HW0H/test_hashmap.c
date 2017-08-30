#include <stdio.h>
#include <assert.h>
#include "hashmap.h"

int main() {
  HashMap* iMap = create_hashmap_int(3);
  assert(hashmap_get(iMap, 2) == NULL);

  void* test_obj = malloc(1);
  hashmap_put(iMap, 2, test_obj);
  assert(hashmap_get(iMap, 2) == test_obj);

  printf("Done");

  return 0;
}