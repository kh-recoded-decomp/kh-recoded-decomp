#include "nitro/types.h"

extern unsigned char gSinFx12Table;
extern unsigned int VEC_Add();
extern unsigned int random_next_scaled();

unsigned int func_ov021_020b1f54(int entry) {
  u32 angle;
  int offset [3];

  angle = random_next_scaled(0x10000);
  offset[0] = (int)*(short *)(&gSinFx12Table + ((int)angle >> 4) * 2) << 1;
  offset[1] = 0;
  offset[2] =
       (int)*(short *)(&gSinFx12Table + (0x400U - ((int)angle >> 4) & 0xfff) * 2) << 1;
  VEC_Add(offset,(void *)(entry + 0x34),(void *)(entry + 0x34));
  return 0;
}
