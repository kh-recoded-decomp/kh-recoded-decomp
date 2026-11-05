#include "nitro/types.h"

extern unsigned int *gTextWindowResourceTable;
extern unsigned int data_ov036_020c3868;
extern unsigned int CreateTaskObject();

unsigned int CreateTextWindowTask(void) {
  void *instance;

  instance = CreateTaskObject(&data_ov036_020c3868,(void *)0x0);
  *gTextWindowResourceTable = instance;
  return *gTextWindowResourceTable;
}
