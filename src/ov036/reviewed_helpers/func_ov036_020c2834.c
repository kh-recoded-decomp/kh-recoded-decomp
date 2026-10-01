#include "nitro/types.h"

extern unsigned int *data_ov036_020c3844;
extern unsigned int data_ov036_020c3848;
extern unsigned int func_0202a448();

unsigned int func_ov036_020c2834(void) {
  void *instance;

  instance = func_0202a448(&data_ov036_020c3848,(void *)0x0);
  *data_ov036_020c3844 = instance;
  return *data_ov036_020c3844;
}
