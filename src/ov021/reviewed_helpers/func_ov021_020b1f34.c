#include "nitro/types.h"

extern unsigned char data_0205356c;
extern unsigned int VEC_Add_01ff9e0c();
extern unsigned int random_next_scaled_0202aa04();

unsigned int func_ov021_020b1f34(int entry) {
  u32 angle;
  int offset [3];

  angle = random_next_scaled_0202aa04(0x10000);
  offset[0] = (int)*(short *)(&data_0205356c + ((int)angle >> 4) * 2) << 1;
  offset[1] = 0;
  offset[2] =
       (int)*(short *)(&data_0205356c + (0x400U - ((int)angle >> 4) & 0xfff) * 2) << 1;
  VEC_Add_01ff9e0c(offset,(void *)(entry + 0x34),(void *)(entry + 0x34));
  return 0;
}
