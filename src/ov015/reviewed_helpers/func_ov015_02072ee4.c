#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov015_0207e964;
extern u8 data_ov015_0207e804;
extern u8 data_ov015_0207e80c;

void func_ov015_02072ee4(char nextState) {
  if (*data_ov015_0207e964 != -1) {
    (**(code **)(&data_ov015_0207e80c + *data_ov015_0207e964 * 0xc))();
  }
  *data_ov015_0207e964 = nextState;
  (**(code **)(&data_ov015_0207e804 + (short)*data_ov015_0207e964 * 0xc))();
}
