#include "nitro/types.h"

extern u32 data_ov039_020bea20;
extern u32 SetMenuButtonsEnabled();

void func_ov039_020bc038(u32 value) {
  SetMenuButtonsEnabled();
  *(u32 *)(data_ov039_020bea20 + 0xca10) = value;
}
