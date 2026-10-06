#include "nitro/types.h"

extern unsigned int G2_GetBG2ScrPtr();
extern unsigned int G2_GetBG3ScrPtr();
extern unsigned int MIi_CpuClearFast();
extern unsigned int DestroyFndObjectList();
extern unsigned int FlushBufferAndRunCallback();
extern unsigned int CallVirtualHandlerSlot1();
extern unsigned int NNSi_FndFreeFromDefaultHeap();
extern unsigned int IsPackedBitSet();
extern unsigned int func_ov036_020c27ec();

void func_ov036_020bee60(int *window) {
  int active;
  unsigned int screen;

  if (window[0x1c] != 0) {
    NNSi_FndFreeFromDefaultHeap(window[0x1c]);
    window[0x1c] = 0;
    if (*window == 0 || *window == 4) {
      *(unsigned int *)window[0x43] = 0;
    }
  }
  active = IsPackedBitSet(window,0);
  if (active != 0) {
    CallVirtualHandlerSlot1(window + 0xf,0);
    FlushBufferAndRunCallback(window + 0xf);
    DestroyFndObjectList(window + 0xf);
    func_ov036_020c27ec(window,0);
  }
  if (window[0xb] == 2) {
    screen = G2_GetBG2ScrPtr();
    MIi_CpuClearFast(0,screen,0x800);
    return;
  }
  screen = G2_GetBG3ScrPtr();
  MIi_CpuClearFast(0,screen,0x800);
}
