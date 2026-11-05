#include "nitro/types.h"

extern u32 data_ov039_020bea20;
extern u32 SetMenuButtonsEnabled();

void SetMenuInputEnabled(u32 value) {
  SetMenuButtonsEnabled();
  *(u32 *)(data_ov039_020bea20 + 0xca10) = value;
}
