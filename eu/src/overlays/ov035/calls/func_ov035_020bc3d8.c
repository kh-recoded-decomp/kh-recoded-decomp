#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov035_020bc508;
extern unsigned int GetSceneTagTracker();
extern unsigned int FindLoadedElementById();
extern unsigned int SetTagRecordArmed();

void func_ov035_020bc3d8(void) {
  int work;
  unsigned int panel;
  unsigned int record;

  work = data_ov035_020bc508.value;
  panel = GetSceneTagTracker();
  if (*(int *)(work + 0x18) == 100) {
    record = FindLoadedElementById(panel,1);
    SetTagRecordArmed(panel,record,1);
  }
}
