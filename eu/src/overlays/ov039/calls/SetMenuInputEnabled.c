#include "nitro/types.h"

extern u32 gMenuOverlayWork;
extern u32 SetMenuButtonsEnabled();

void SetMenuInputEnabled(u32 value) {
  SetMenuButtonsEnabled();
  *(u32 *)(gMenuOverlayWork + 0xca10) = value;
}
