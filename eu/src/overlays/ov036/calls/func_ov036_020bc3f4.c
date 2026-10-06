#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov036_020c3940;

void func_ov036_020bc3f4(void) {
  *(u16 *)(data_ov036_020c3940.value + 6) = *(u16 *)(data_ov036_020c3940.value + 6) & 0xfffd;
}
