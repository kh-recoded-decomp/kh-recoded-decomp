#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020c3920;
extern unsigned int func_01ff8830();

void func_ov036_020bd9e0(void) {
  func_01ff8830(data_020c3920.value + 0x10ec,0,0x10);
}
