#include "nitro/types.h"

extern unsigned int *gMenuCursorState;
extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern unsigned int func_01ff8830();

void InitMenuCursorState_020666c8(unsigned int value) {
  if (gMenuCursorState != (void *)0x0) {
    NNSi_FndFreeFromDefaultHeap_0202a1c4(gMenuCursorState);
    gMenuCursorState = (void *)0x0;
  }
  gMenuCursorState = NNSi_FndAllocFromDefaultHeap_0202a178(0x2c);
  func_01ff8830(gMenuCursorState,0,0x2c);
  *gMenuCursorState = value;
}
