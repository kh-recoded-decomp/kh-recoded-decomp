#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov002_0206c464;
extern u8 data_ov002_0206c3c8;
extern u8 data_ov002_0206c3d0;

void func_ov002_02064f6c(char nextState) {
  if (*data_ov002_0206c464 != -1) {
    (**(code **)(&data_ov002_0206c3d0 + *data_ov002_0206c464 * 0xc))();
  }
  *data_ov002_0206c464 = nextState;
  (**(code **)(&data_ov002_0206c3c8 + (short)*data_ov002_0206c464 * 0xc))();
}
