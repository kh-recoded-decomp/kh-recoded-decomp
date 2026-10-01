#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020c3920;

void func_ov036_020bc3d4(void) {
  *(u16 *)(data_020c3920.value + 6) = *(u16 *)(data_020c3920.value + 6) & 0xfffd;
}
