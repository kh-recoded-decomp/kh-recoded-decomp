#include "nitro/types.h"

extern u32 GetActiveMenuScene();
extern u32 MoveCursorToElement();

void MovePopupCursorOnDirectionalInput(u32 event,u32 buttons) {
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
