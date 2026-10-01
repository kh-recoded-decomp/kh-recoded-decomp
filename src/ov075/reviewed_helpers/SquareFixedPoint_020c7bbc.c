#include "nitro/types.h"

#define false 0
#define true 1


u32 SquareFixedPoint_020c7bbc(int value)

{
  s64 product;
  
  product = (s64)value * (s64)value + 0x800;
  return (int)(product >> 12);
}
