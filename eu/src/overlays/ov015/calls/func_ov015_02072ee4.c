#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov015_0207e964;
extern u8 gWirelessStateInitCallback;
extern u8 gWirelessStateHandlers;

void func_ov015_02072ee4(char nextState) {
  if (*data_ov015_0207e964 != -1) {
    (**(code **)(&gWirelessStateHandlers + *data_ov015_0207e964 * 0xc))();
  }
  *data_ov015_0207e964 = nextState;
  (**(code **)(&gWirelessStateInitCallback + (short)*data_ov015_0207e964 * 0xc))();
}
