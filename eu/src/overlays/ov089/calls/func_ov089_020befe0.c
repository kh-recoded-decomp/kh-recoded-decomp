#include "nitro/types.h"

extern u32 func_ov039_020bc638();
extern u32 MoveCursorToElement();

void func_ov089_020befe0(u32 event,u32 buttons) {
  int work;

  work = func_ov039_020bc638();
  if (*(int *)(work + 0x8fc) == 0) {
    return;
  }
  if ((buttons & 0xf0) == 0) {
    return;
  }
  MoveCursorToElement(work,event,1);
}
