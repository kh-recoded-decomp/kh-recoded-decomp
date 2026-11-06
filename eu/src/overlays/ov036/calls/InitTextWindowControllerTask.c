#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdateTextWindowControllerNoOp();
extern unsigned int OpenTextPanelWithGraphicsBackup();
extern unsigned int UpdateTextPanelPromptCallback();
extern unsigned int CloseOverlayPanel();
extern unsigned int gTextWindowBgTaskWorkPointerStorage;
extern unsigned int ConfigureOverlay036BackgroundControls();
extern unsigned int setDualArrayEntry();
extern unsigned int GetRunningTaskWork();
extern unsigned int CreateTextWindowTask();
extern unsigned int SetupOverlayVramBanks();

code * InitTextWindowControllerTask(void) {
  unsigned int instance;

  gTextWindowBgTaskWorkPointerStorage = GetRunningTaskWork();
  SetupOverlayVramBanks();
  ConfigureOverlay036BackgroundControls();
  setDualArrayEntry(0,OpenTextPanelWithGraphicsBackup,0);
  setDualArrayEntry(1,UpdateTextPanelPromptCallback,0);
  setDualArrayEntry(2,CloseOverlayPanel,0);
  instance = CreateTextWindowTask();
  *(unsigned int *)(gTextWindowBgTaskWorkPointerStorage + 4) = instance;
  return UpdateTextWindowControllerNoOp;
}
