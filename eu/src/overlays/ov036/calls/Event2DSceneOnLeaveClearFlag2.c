#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov036_020c3940;

void Event2DSceneOnLeaveClearFlag2(void) {
  *(u16 *)(data_ov036_020c3940.value + 6) = *(u16 *)(data_ov036_020c3940.value + 6) & 0xfffd;
}
