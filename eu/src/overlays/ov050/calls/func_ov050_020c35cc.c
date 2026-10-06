#include "nitro/types.h"

extern unsigned int AbsDotProduct();
extern unsigned int IsFacingContactNormal();

unsigned int func_ov050_020c35cc(unsigned int object,int probe,unsigned int context,int actor) {
  int hit;

  if ((*(int *)(probe + 0x10) <= 0) &&
     (hit = AbsDotProduct((void *)(actor + 0x20),(void *)(probe + 4)),
     hit < 0x10)) {
    return 0;
  }
  hit = IsFacingContactNormal(object,probe + 4);
  if (hit == 0) {
    return 0;
  }
  return 1;
}
