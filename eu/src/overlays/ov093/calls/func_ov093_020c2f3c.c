#include "nitro/types.h"

extern u32 CallVirtualHandlerSlot1();
extern u32 DestroyFndObjectList();
extern u32 FlushBufferAndRunCallback();
extern u32 G2S_GetBG2ScrPtr();
extern u32 NNSi_FndFreeFromDefaultHeap();
extern u32 MIi_CpuClearFast();
extern u32 func_ov093_020c3bc4();
extern u32 func_ov093_020c3bd8();

void func_ov093_020c2f3c(int work) {
  int ready;
  void *screen;

  ready = func_ov093_020c3bd8(work,1);
  if (ready != 0) {
    if (*(void **)(work + 0x4c) != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap(*(void **)(work + 0x4c));
      *(u32 *)(work + 0x4c) = 0;
      CallVirtualHandlerSlot1((void *)(work + 0x18),0);
      FlushBufferAndRunCallback((void *)(work + 0x18));
      DestroyFndObjectList(work + 0x18);
    }
    func_ov093_020c3bc4(work,1);
  }
  screen = G2S_GetBG2ScrPtr();
  MIi_CpuClearFast(0,screen,0x800);
}
