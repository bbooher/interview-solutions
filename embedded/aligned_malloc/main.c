
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DEBUG 1

#if DEBUG == 1
#include <stdio.h>
#else
#define printf(...) ((void)0)
#endif


#define PTR_ARITHMETIC 0  // 0: Use pointer arithmetic, 1: Use pointer storage

void *aligned_malloc(size_t bytes, size_t alignment)
{
  uintptr_t *p1; // initial block
  uintptr_t *p2; // aligned block

  if ((p1 = (uintptr_t *)malloc(bytes + alignment + sizeof(uintptr_t))) == NULL) {
    return NULL;
  }

  // End of allocated block
  uintptr_t addr = (uintptr_t)p1 + alignment + sizeof(uintptr_t);
  // Get aligned block 'highest' in memory
  p2 = (uintptr_t *)(addr - (addr % alignment));

#if PTR_ARITHMETIC == 1
  // Store the original block pointer before the aligned block, for free
  uintptr_t *p2_store = p2 - 1;
  *(p2_store) = (uintptr_t)p1;
#else
  // Alternate approach
  uintptr_t p2_store = (uintptr_t)p2 - sizeof(uintptr_t);
  *(uintptr_t *)p2_store = (uintptr_t)p1;
#endif

  printf("Original block: %p\n", p1);
  printf("Aligned block: %p\n", p2);

  return (void *)p2;
}

void aligned_free(void *p)
{
#if PTR_ARITHMETIC == 1
  printf("Freeing: %p\n", (uintptr_t *)(*((uintptr_t *)p-1)));
  free((uintptr_t *)(*((uintptr_t *)p-1)));
#else
  printf("Freeing: %p\n", (uintptr_t *)(*(uintptr_t *)((uintptr_t)p - sizeof(uintptr_t))));
  free((uintptr_t *)(*(uintptr_t *)((uintptr_t)p - sizeof(uintptr_t))));
#endif
}

int main(void)
{
  char *p = (char *)aligned_malloc(100, 128);
  printf("Alloc returned: %p\n", p);

  char val[100] = {0};
  val[99] = 6;

  memcpy(p, val, 100);

  printf("Value at 99: %d\n", *(p+99)); // Dereference pointer
  printf("Value at 99: %d\n", p[99]);   // Array subscript

  aligned_free(p);

  return 0;
}
