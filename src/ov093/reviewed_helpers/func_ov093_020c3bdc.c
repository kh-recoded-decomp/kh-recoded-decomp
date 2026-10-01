#include "nitro/types.h"

extern unsigned int *data_ov093_020c50e4;
extern unsigned int data_ov093_020c50b8;
extern unsigned int func_0202a448();

unsigned int func_ov093_020c3bdc(void *initialValues) {
  void *instance;

  instance = func_0202a448(&data_ov093_020c50b8,initialValues);
  *data_ov093_020c50e4 = instance;
  return *data_ov093_020c50e4;
}
