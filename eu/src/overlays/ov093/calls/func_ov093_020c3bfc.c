#include "nitro/types.h"

extern unsigned int *data_ov093_020c5104;
extern unsigned int data_ov093_020c50d8;
extern unsigned int func_0202a45c();

unsigned int func_ov093_020c3bfc(void *initialValues) {
  void *instance;

  instance = func_0202a45c(&data_ov093_020c50d8,initialValues);
  *data_ov093_020c5104 = instance;
  return *data_ov093_020c5104;
}
