#include "nitro/types.h"

extern u32 CallVirtualHandlerSlot1_02001574();
extern u32 DestroyFndObjectList_020014f0();
extern u32 FlushBufferAndRunCallback_0200153c();
extern u32 G2S_GetBG2ScrPtr_02006f0c();
extern u32 NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern u32 func_01ff8740();
extern u32 func_ov093_020c3ba4();
extern u32 func_ov093_020c3bb8();

void func_ov093_020c2f1c(int work) {
  int ready;
  void *screen;

  ready = func_ov093_020c3bb8(work,1);
  if (ready != 0) {
    if (*(void **)(work + 0x4c) != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(work + 0x4c));
      *(u32 *)(work + 0x4c) = 0;
      CallVirtualHandlerSlot1_02001574((void *)(work + 0x18),0);
      FlushBufferAndRunCallback_0200153c((void *)(work + 0x18));
      DestroyFndObjectList_020014f0(work + 0x18);
    }
    func_ov093_020c3ba4(work,1);
  }
  screen = G2S_GetBG2ScrPtr_02006f0c();
  func_01ff8740(0,screen,0x800);
}
