#include "nitro/types.h"

extern unsigned int *data_ov091_020c375c;
extern unsigned char data_ov091_020c2c88;
extern unsigned int func_0202a45c();

unsigned int func_ov091_020c27bc(void *initialValues) {
  void *instance;

  instance = func_0202a45c(&data_ov091_020c2c88 + 0x0c,initialValues);
  *data_ov091_020c375c = instance;
  return *data_ov091_020c375c;
}
