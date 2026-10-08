#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdateTextWindows();
extern unsigned int gTextWindowResourceTable;
extern unsigned int data_ov036_020c394c;
extern unsigned int InitOverlayObjManager();
extern unsigned int NNSi_FndGetCurrentRootHeap();
extern unsigned int MIi_CpuClearFast();
extern unsigned int func_0204f5a0();
extern unsigned int LoadTextWindowBackground();
extern unsigned int func_ov036_020beb7c();
extern unsigned int SetTimerDuration();

code * func_ov036_020be858(void) {
  int index;

  data_ov036_020c394c = NNSi_FndGetCurrentRootHeap();
  index = 0;
  MIi_CpuClearFast(0,gTextWindowResourceTable,0x68b4);
  *(unsigned int *)(gTextWindowResourceTable + 0x6458) = 1;
  *(unsigned int *)(gTextWindowResourceTable + 0x68a0) = 0xffffffff;
  *(unsigned int *)(gTextWindowResourceTable + 0x682c) = 0;
  do {
    SetTimerDuration(gTextWindowResourceTable + 0x64fc + index * 0x110,0);
    index = index + 1;
  } while (index < 3);
  func_0204f5a0((void *)(gTextWindowResourceTable + 0x6830),(void *)0x0);
  LoadTextWindowBackground();
  func_ov036_020beb7c();
  InitOverlayObjManager();
  return UpdateTextWindows;
}
