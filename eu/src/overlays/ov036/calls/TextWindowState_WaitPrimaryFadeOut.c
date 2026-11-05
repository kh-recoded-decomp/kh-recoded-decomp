#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 SetRecordEntryEnabled();
extern u32 SetTextWindowState();
extern u32 GetTextWindowState();

void TextWindowState_WaitPrimaryFadeOut(int work) {
  int state;

  state = GetTextWindowState(gTextWindowResourceTable + 0x64fc);
  if (state != 9) {
    return;
  }
  SetRecordEntryEnabled(work + 0xb4,0);
  SetRecordEntryEnabled(work + 0xf4,0);
  SetTextWindowState(work,9);
}
