#include "nitro/types.h"

extern unsigned int *data_ov093_020c5104;
extern unsigned int data_ov093_020c50d8;
extern unsigned int CreateTaskObject();

unsigned int CreatePopupManager(void *initialValues) {
  void *instance;

  instance = CreateTaskObject(&data_ov093_020c50d8,initialValues);
  *data_ov093_020c5104 = instance;
  return *data_ov093_020c5104;
}
