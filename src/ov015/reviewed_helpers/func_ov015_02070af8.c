#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov015_0207e960;
extern u8 data_ov015_0207e780;
extern u8 data_ov015_0207e788;

void func_ov015_02070af8(char nextState) {
  if (*data_ov015_0207e960 != -1) {
    (**(code **)(&data_ov015_0207e788 + *data_ov015_0207e960 * 0xc))();
  }
  *data_ov015_0207e960 = nextState;
  (**(code **)(&data_ov015_0207e780 + (short)*data_ov015_0207e960 * 0xc))();
}
