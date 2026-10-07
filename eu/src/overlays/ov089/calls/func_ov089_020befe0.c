#include "nitro/types.h"

extern u32 GetActiveMenuScene();
extern u32 MoveCursorToElement();

void func_ov089_020befe0(u32 event,u32 buttons) {
  int work;

  work = GetActiveMenuScene();
  if (*(int *)(work + 0x8fc) == 0) {
    return;
  }
  if ((buttons & 0xf0) == 0) {
    return;
  }
  MoveCursorToElement(work,event,1);
}
