#include "nitro/types.h"

extern u32 GetActiveMenuScene();
extern u32 PopPanelState_020c6218();

void HandlePanelBackWidget(void) {
  int work;

  work = GetActiveMenuScene();
  if (*(int *)(work + 0x10) != 0) {
    return;
  }
  PopPanelState_020c6218(work,1);
}
