#include "nitro/types.h"

extern u16 data_02060500;
extern unsigned int SetPanelState();
extern unsigned int HasRecentTouchPoints();

unsigned int func_ov000_02062318(void *work) {
  int timerOrInput;
  unsigned int nextState;

  nextState = 0xffffffff;
  timerOrInput = *(int *)((int)work + 0x24) + 1;
  *(int *)((int)work + 0x24) = timerOrInput;
  if (timerOrInput >= 0x3c) {
    switch(*(unsigned int *)((int)work + 0x2c)) {
    case 0:
      SetPanelState(work,0,0x1e,0x1e);
      nextState = 1;
      break;
    case 1:
      SetPanelState(work,0,0x1e,0x1e);
      nextState = 2;
      break;
    case 2:
      SetPanelState(work,0,0x1e,0x1e);
      nextState = 3;
      break;
    case 3:
      SetPanelState(work,0,0x1e,0x1e);
      nextState = 4;
      break;
    default:
      SetPanelState(work,0,0x1e,0);
      nextState = 5;
    }
  }
  timerOrInput = HasRecentTouchPoints();
  if ((*(int *)((int)work + 0x2c) == 0) &&
     (((data_02060500 & 9) != 0 || ((*(int *)((int)work + 0x28) == 0 && (timerOrInput != 0)))))) {
    *(unsigned int *)((int)work + 0x24) = 0x3c;
  }
  *(int *)((int)work + 0x28) = timerOrInput;
  return nextState;
}
