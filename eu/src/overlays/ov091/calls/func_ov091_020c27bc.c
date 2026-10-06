#include "nitro/types.h"

extern unsigned int *data_ov091_020c375c;
extern unsigned int data_ov091_020c2c94;
extern unsigned int func_0202a45c();

unsigned int func_ov091_020c27bc(void *initialValues) {
  void *instance;

  instance = func_0202a45c(&data_ov091_020c2c94,initialValues);
  *data_ov091_020c375c = instance;
  return *data_ov091_020c375c;
}
