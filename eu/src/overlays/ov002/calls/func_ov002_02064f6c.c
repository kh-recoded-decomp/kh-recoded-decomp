#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov002_0206c464;
extern u8 gMenuIntroCallback;
extern u8 gMenuStateHandlers;

void func_ov002_02064f6c(char nextState) {
  if (*data_ov002_0206c464 != -1) {
    (**(code **)(&gMenuStateHandlers + *data_ov002_0206c464 * 0xc))();
  }
  *data_ov002_0206c464 = nextState;
  (**(code **)(&gMenuIntroCallback + (short)*data_ov002_0206c464 * 0xc))();
}
