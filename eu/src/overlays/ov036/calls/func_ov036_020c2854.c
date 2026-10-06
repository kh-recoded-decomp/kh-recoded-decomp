#include "nitro/types.h"

extern unsigned int *gTextWindowResourceTable;
extern unsigned int data_ov036_020c3868;
extern unsigned int func_0202a45c();

unsigned int func_ov036_020c2854(void) {
  void *instance;

  instance = func_0202a45c(&data_ov036_020c3868,(void *)0x0);
  *gTextWindowResourceTable = instance;
  return *gTextWindowResourceTable;
}
