#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov036_020c2e10();
extern unsigned int func_ov036_020c32bc();
extern unsigned int func_ov036_020c32e4();
extern unsigned int CloseOverlayPanel();
extern unsigned int data_ov036_020ca204;
extern unsigned int ConfigureOverlay036BackgroundControls();
extern unsigned int setDualArrayEntry();
extern unsigned int NNSi_FndGetCurrentRootHeap();
extern unsigned int func_ov036_020c2854();
extern unsigned int SetupOverlayVramBanks();

code * func_ov036_020c2d68(void) {
  unsigned int instance;

  data_ov036_020ca204 = NNSi_FndGetCurrentRootHeap();
  SetupOverlayVramBanks();
  ConfigureOverlay036BackgroundControls();
  setDualArrayEntry(0,func_ov036_020c32bc,0);
  setDualArrayEntry(1,func_ov036_020c32e4,0);
  setDualArrayEntry(2,CloseOverlayPanel,0);
  instance = func_ov036_020c2854();
  *(unsigned int *)(data_ov036_020ca204 + 4) = instance;
  return func_ov036_020c2e10;
}
