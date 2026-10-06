#include "nitro/types.h"

extern unsigned int data_ov039_020bea20;
extern unsigned int RuntimeState_SetMode();
extern unsigned int SetMenuButtonsEnabled();
extern unsigned int func_ov039_020bcf40();
extern unsigned int func_ov039_020bd074();

void func_ov039_020bb4c8(void) {
  int work;

  work = data_ov039_020bea20;
  func_ov039_020bcf40(*(unsigned int *)(data_ov039_020bea20 + 0xc998));
  func_ov039_020bd074(*(unsigned int *)(work + 0xc99c));
  if (((u32)*(int *)(work + 0xc9e8) << 29) >> 31 == 0) {
    return;
  }
  SetMenuButtonsEnabled(1);
  RuntimeState_SetMode(3);
}
