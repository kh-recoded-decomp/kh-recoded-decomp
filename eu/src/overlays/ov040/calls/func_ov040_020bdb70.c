#include "nitro/types.h"

extern u32 data_ov040_020be280;
extern u32 DrawNodeWithExplicitProjection();

void func_ov040_020bdb70(void) {
  DrawNodeWithExplicitProjection
            (data_ov040_020be280,(void *)((int)data_ov040_020be280 + 0x104),0x2400,-0x2400,-0x3000
             ,0x3000);
}
