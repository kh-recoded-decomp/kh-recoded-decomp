#include "nitro/types.h"

extern unsigned int *gTrophyPopupWorkStorage;
extern unsigned int gTrophyPopupTaskDescriptorStorage;
extern unsigned int CreateTaskObject();

unsigned int CreatePopupManager(void *initialValues) {
  void *instance;

  instance = CreateTaskObject(&gTrophyPopupTaskDescriptorStorage,initialValues);
  *gTrophyPopupWorkStorage = instance;
  return *gTrophyPopupWorkStorage;
}
