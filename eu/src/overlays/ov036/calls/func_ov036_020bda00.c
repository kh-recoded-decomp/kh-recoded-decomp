#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov036_020c3940;
extern unsigned int MI_CpuFill8();

void func_ov036_020bda00(void) {
  MI_CpuFill8(data_ov036_020c3940.value + 0x10ec,0,0x10);
}
