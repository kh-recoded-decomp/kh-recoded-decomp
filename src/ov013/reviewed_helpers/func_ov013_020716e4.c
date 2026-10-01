#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov013_02074ce0;
extern u8 data_ov013_02074bbc;
extern u8 data_ov013_02074bc4;

void func_ov013_020716e4(char nextState) {
  if (*data_ov013_02074ce0 != -1) {
    (**(code **)(&data_ov013_02074bc4 + *data_ov013_02074ce0 * 0xc))();
  }
  *data_ov013_02074ce0 = nextState;
  (**(code **)(&data_ov013_02074bbc + (short)*data_ov013_02074ce0 * 0xc))();
}
