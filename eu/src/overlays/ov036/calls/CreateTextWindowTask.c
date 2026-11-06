#include "nitro/types.h"

extern unsigned int *gTextWindowResourceTable;
extern unsigned int gTextWindowTaskClass;
extern unsigned int CreateTaskObject();

unsigned int CreateTextWindowTask(void) {
  void *instance;

  instance = CreateTaskObject(&gTextWindowTaskClass,(void *)0x0);
  *gTextWindowResourceTable = instance;
  return *gTextWindowResourceTable;
}
