#include "nitro/types.h"

extern u32 data_ov103_020c0500;
extern u32 MIi_CpuClearFast();
extern u32 func_ov039_020bcda0();
extern u32 func_ov103_020bef14();
extern u32 LoadGraphicsResources();
extern u32 func_ov103_020bf0c4();
extern u32 func_ov103_020bf1bc();
extern u32 func_ov103_020bf3bc();
extern u32 func_ov103_020bf5e8();
extern u32 SetupListPanel();
extern u32 RefreshUnlockedEntries();
extern u32 SetScenePhase();

void func_ov103_020c033c(int *work) {
  int selection;

  selection = func_ov039_020bcda0();
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
  func_ov103_020bef14(work);
  LoadGraphicsResources(work);
  func_ov103_020bf0c4(work);
  func_ov103_020bf1bc(work);
  func_ov103_020bf5e8(work);
  SetupListPanel(&data_ov103_020c0500,work);
  func_ov103_020bf3bc(0xffffffff,work);
  SetScenePhase(2,work);
}
