#include <stdio.h>
#include <stdint.h>

uint32_t no_plus_operator_add(uint32_t a, uint32_t b)
{
  uint32_t result = a ^ b;
  uint32_t carry = (a & b) << 1;
  
  while (carry) {
    uint32_t tmp_res = result ^ carry;
    carry = (result & carry) << 1;
    
    result = tmp_res;
  };
  
  return result;
}

int main(void)
{
  printf("5 + 7 = %d\n", no_plus_operator_add(5, 7));
  printf("22 + 42 = %d\n", no_plus_operator_add(22, 42));
  printf("13 + 0 = %d\n", no_plus_operator_add(13, 0));

  return 0;
}
