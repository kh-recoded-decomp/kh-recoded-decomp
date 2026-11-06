#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState gAreaSceneGaugeGlobalsStorage;
extern unsigned int GetSceneTagTracker();
extern unsigned int FindLoadedElementById();
extern unsigned int SetTagRecordArmed();

void ArmAreaSequence1AtGaugeMax(void) {
  int work;
  unsigned int panel;
  unsigned int record;

  work = gAreaSceneGaugeGlobalsStorage.value;
  panel = GetSceneTagTracker();
  if (*(int *)(work + 0x18) == 100) {
    record = FindLoadedElementById(panel,1);
    SetTagRecordArmed(panel,record,1);
  }
}
