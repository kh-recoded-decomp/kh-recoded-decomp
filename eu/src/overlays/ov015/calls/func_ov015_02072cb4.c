#include "nitro/types.h"

extern signed char *data_ov015_0207e964;
extern int func_ov015_02072ee4();

void func_ov015_02072cb4(void) {
  if (4 < ((*data_ov015_0207e964 + -3) * 0x1000000 >> 0x18 & 0xffU)) {
    return;
  }
  func_ov015_02072ee4(2);
}
