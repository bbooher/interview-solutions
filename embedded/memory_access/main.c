
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// ----------------------------------------------------------------------------
// Memory Access Macro API

// System physical memory access (uintptr_t is guaranteed to be the same size as a pointer in C99 or later)
// Could also use uint32_t, uint64_t, etc. for specific register sizes or void * for generic
#define MEM_PTR(addr) ((volatile uintptr_t *)(addr))            // Pointer to register at address
#define MEM_SET_VALUE(addr, value) (*MEM_PTR(addr) = value)
#define MEM_SET_MASK(addr, value) (*MEM_PTR(addr) |= value)     // Not atomic
#define MEM_GET(addr) (*MEM_PTR(addr))
#define MEM_CLEAR_VALUE(addr) (*MEM_PTR(addr) = 0)
#define MEM_CLEAR_MASK(addr, value) (*MEM_PTR(addr) &= ~value)  // Not atomic
// ----------------------------------------------------------------------------

// Example physical memory address.
#define SOME_ADDRESS 0x12345678
#define SOME_ADDRESS_OFFSET 0x100

// ----------------------------------------------------------------------------
// Register Access with Bitfield

typedef struct {
  union {
    uint32_t u32;
    struct {
      uint32_t b0 : 1;
      uint32_t b1 : 1;
      uint32_t b2 : 1;
      uint32_t b3 : 1;
      uint32_t b4 : 1;
      uint32_t b5 : 1;
      uint32_t b6 : 1;
      uint32_t b7 : 1;
      uint32_t b8 : 1;
      uint32_t b9 : 1;
      uint32_t b10 : 1;
      uint32_t b11 : 1;
      uint32_t b12 : 1;
      uint32_t b13 : 1;
      uint32_t b14 : 1;
      uint32_t b15 : 1;
      uint32_t b16 : 1;
      uint32_t b17 : 1;
      uint32_t b18 : 1;
      uint32_t b19 : 1;
      uint32_t b20 : 1;
      uint32_t b21 : 1;
      uint32_t b22 : 1;
      uint32_t b23 : 1;
      uint32_t b24 : 1;
      uint32_t b25 : 1;
      uint32_t b26 : 1;
      uint32_t b27 : 1;
      uint32_t b28 : 1;
      uint32_t b29 : 1;
      uint32_t b30 : 1;
      uint32_t b31 : 1;
    } bits;
  } value;
} register32_t;


int main(void)
{
  volatile uintptr_t *some_addr = MEM_PTR(SOME_ADDRESS);

  // Get then set
  uintptr_t some_addr_value = MEM_GET(SOME_ADDRESS);
  MEM_SET_VALUE(SOME_ADDRESS, some_addr_value | 0x1234);

  // Reset the register
  MEM_CLEAR_VALUE(SOME_ADDRESS);
  MEM_SET_VALUE(SOME_ADDRESS, some_addr_value);

  // Get then set with mask
  MEM_SET_MASK(SOME_ADDRESS, 0x1234);

  printf("Address of register: %p\n", some_addr);
  printf("Value of register: %lx\n", (uintptr_t)MEM_GET(SOME_ADDRESS));   // %lx for uintptr_t on 64-bit systems, %x for 32-bit (kind of annoying)

  volatile uintptr_t *some_addr_offset = MEM_PTR(SOME_ADDRESS + SOME_ADDRESS_OFFSET);
  uintptr_t some_addr_offset_value = MEM_GET(*some_addr_offset);

  // ----------------------------------------------------------------------------

  register32_t reg32;
  reg32.value.u32 = some_addr_offset_value; // Read value from memory into register struct
  reg32.value.bits.b0 = 1;                  // Set bit 0 to 1 (not synced to memory)

  MEM_SET_VALUE(some_addr_offset, reg32.value.u32); // Write value back to memory

  return 0;
}
