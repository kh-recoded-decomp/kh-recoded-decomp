#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov036_020c2df0();
extern unsigned int func_ov036_020c329c();
extern unsigned int func_ov036_020c32c4();
extern unsigned int func_ov036_020c32d4();
extern unsigned int data_ov036_020ca1e4;
extern unsigned int ConfigureOverlay036BackgroundControls();
extern unsigned int func_02025448();
extern unsigned int func_0202a764();
extern unsigned int func_ov036_020c2834();
extern unsigned int func_ov036_020c2df8();

code * func_ov036_020c2d48(void) {
  unsigned int instance;

  data_ov036_020ca1e4 = func_0202a764();
  func_ov036_020c2df8();
  ConfigureOverlay036BackgroundControls();
  func_02025448(0,func_ov036_020c329c,0);
  func_02025448(1,func_ov036_020c32c4,0);
  func_02025448(2,func_ov036_020c32d4,0);
  instance = func_ov036_020c2834();
  *(unsigned int *)(data_ov036_020ca1e4 + 4) = instance;
  return func_ov036_020c2df0;
}
