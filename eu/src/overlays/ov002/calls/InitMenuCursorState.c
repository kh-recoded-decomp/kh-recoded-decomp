#include "nitro/types.h"

extern unsigned int *gMenuCursorState;
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int NNSi_FndFreeFromDefaultHeap();
extern unsigned int MI_CpuFill8();

void InitMenuCursorState(unsigned int value) {
  if (gMenuCursorState != (void *)0x0) {
    NNSi_FndFreeFromDefaultHeap(gMenuCursorState);
    gMenuCursorState = (void *)0x0;
  }
  gMenuCursorState = NNSi_FndAllocFromDefaultHeap(0x2c);
  MI_CpuFill8(gMenuCursorState,0,0x2c);
  *gMenuCursorState = value;
}
