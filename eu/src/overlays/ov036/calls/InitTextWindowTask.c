#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int UpdateTextWindows();
extern unsigned int gTextWindowResourceTable;
extern unsigned int data_ov036_020c394c;
extern unsigned int InitOverlayObjManager();
extern unsigned int GetRunningTaskWork();
extern unsigned int MIi_CpuClearFast();
extern unsigned int InitKeyRepeatState();
extern unsigned int LoadTextWindowBackground();
extern unsigned int LoadTextWindowFonts();
extern unsigned int SetTextWindowState();

code * InitTextWindowTask(void) {
  int index;

  data_ov036_020c394c = GetRunningTaskWork();
  index = 0;
  MIi_CpuClearFast(0,gTextWindowResourceTable,0x68b4);
  *(unsigned int *)(gTextWindowResourceTable + 0x6458) = 1;
  *(unsigned int *)(gTextWindowResourceTable + 0x68a0) = 0xffffffff;
  *(unsigned int *)(gTextWindowResourceTable + 0x682c) = 0;
  do {
    SetTextWindowState(gTextWindowResourceTable + 0x64fc + index * 0x110,0);
    index = index + 1;
  } while (index < 3);
  InitKeyRepeatState((void *)(gTextWindowResourceTable + 0x6830),(void *)0x0);
  LoadTextWindowBackground();
  LoadTextWindowFonts();
  InitOverlayObjManager();
  return UpdateTextWindows;
}
