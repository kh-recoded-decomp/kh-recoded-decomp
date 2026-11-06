#include "nitro/types.h"

extern u32 gTheaterReportListConfig;
extern u32 MIi_CpuClearFast();
extern u32 RuntimeState_GetObjectId();
extern u32 LoadTheaterReportMessageContainers();
extern u32 LoadGraphicsResources();
extern u32 LoadEntryBackground_020bf0c4();
extern u32 InitTextLayers_020bf1bc();
typedef struct TheaterState TheaterState;
extern void RedrawTheaterReportText(int unused, TheaterState *state);
extern u32 CreateTheaterReportSlotEntries();
extern u32 SetupListPanel();
extern u32 RefreshUnlockedEntries();
extern u32 SetScenePhase();

void InitTheaterReportScreen(int *work) {
  int selection;

  selection = RuntimeState_GetObjectId();
  MIi_CpuClearFast(0,work,0xcbc4);
  if (selection < 0) {
    selection = 0;
  }
  *work = selection;
  work[1] = -0x10;
  work[0x32e2] = 0;
  work[0x32e4] = 0;
  work[0x32e3] = 0;
  RefreshUnlockedEntries(work);
  LoadTheaterReportMessageContainers(work);
  LoadGraphicsResources(work);
  LoadEntryBackground_020bf0c4(work);
  InitTextLayers_020bf1bc(work);
  CreateTheaterReportSlotEntries(work);
  SetupListPanel(&gTheaterReportListConfig,work);
  RedrawTheaterReportText(0xffffffff,(TheaterState *)work);
  SetScenePhase(2,work);
}
