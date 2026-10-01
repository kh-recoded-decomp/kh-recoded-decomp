#include "nitro/types.h"

extern u32 data_ov040_020be260;
extern u32 DrawNodeWithExplicitProjection_0202f1b0();

void func_ov040_020bdb50(void) {
  DrawNodeWithExplicitProjection_0202f1b0
            (data_ov040_020be260,(void *)((int)data_ov040_020be260 + 0x104),0x2400,-0x2400,-0x3000
             ,0x3000);
}
