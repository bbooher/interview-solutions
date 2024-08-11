
#include <stdio.h>
#include <string.h>

void print_fibonacci(int n) {
  if (n <= 0) {
    printf("Invalid fibonacci size\n");
    return;
  }

  if (n <= 2) {
    printf("%3d", 1);
    return;
  }
  
  if (n > 2) {
    int fib[n];
    fib[0] = 1;
    fib[1] = 1;
    printf("%3d %3d", fib[0], fib[1]);
    for (int i = 2; i < n; i++) {
      fib[i] = fib[i - 1] + fib[i - 2];
      printf("%3d", fib[i]);
    }
  }
  printf("\n");
}

int main()
{
    print_fibonacci(7);

    return 0;
}
