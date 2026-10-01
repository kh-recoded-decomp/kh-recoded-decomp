#include "nitro/types.h"

extern unsigned int AbsDotProduct_0204a96c();
extern unsigned int func_020349d8();

unsigned int func_ov050_020c35ac(unsigned int object,int probe,unsigned int context,int actor) {
  int hit;

  if ((*(int *)(probe + 0x10) <= 0) &&
     (hit = AbsDotProduct_0204a96c((void *)(actor + 0x20),(void *)(probe + 4)),
     hit < 0x10)) {
    return 0;
  }
  hit = func_020349d8(object,probe + 4);
  if (hit == 0) {
    return 0;
  }
  return 1;
}
