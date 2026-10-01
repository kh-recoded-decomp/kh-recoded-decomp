#include "nitro/types.h"

extern u32 data_ov039_020bea00;
extern u32 func_ov039_020bae84();

void func_ov039_020bc018(u32 value) {
  func_ov039_020bae84();
  *(u32 *)(data_ov039_020bea00 + 0xca10) = value;
}
