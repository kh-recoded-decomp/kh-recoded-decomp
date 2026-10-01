#include "nitro/types.h"

extern unsigned int *data_ov091_020c373c;
extern unsigned int data_ov091_020c2c74;
extern unsigned int func_0202a448();

unsigned int func_ov091_020c279c(void *initialValues) {
  void *instance;

  instance = func_0202a448(&data_ov091_020c2c74,initialValues);
  *data_ov091_020c373c = instance;
  return *data_ov091_020c373c;
}
