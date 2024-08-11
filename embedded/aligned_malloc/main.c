
#include <stdlib.h>

void *aligned_malloc(size_t required_bytes, size_t alignment)
{
  void *p1; // initial block
  void *p2; // aligned block

  if ((p1 = (void *)malloc(required_bytes + alignment + sizeof(size_t))) == NULL) {
    return NULL;
  }

  size_t addr = (size_t)p1 + alignment + sizeof(size_t);
  p2 = (void *)(addr - (addr % alignment));
  *((size_t *)p2-1) = (size_t)p1;

  return p2;
}

void aligned_free(void *p)
{
  free((void *)(*((size_t *)p-1)));
}

int main(void)
{

  return 0;
}
