#include "nitro/types.h"

extern u32 CallVirtualHandlerSlot1();
extern u32 DestroyFndObjectList();
extern u32 FlushBufferAndRunCallback();
extern u32 G2S_GetBG2ScrPtr();
extern u32 NNSi_FndFreeFromDefaultHeap();
extern u32 MIi_CpuClearFast();
extern u32 TrophyPopup_ClearFlags();
extern u32 TrophyPopup_GetMaskedFlags();

void ReleasePopupGraphics(int work) {
  int ready;
  void *screen;

  ready = TrophyPopup_GetMaskedFlags(work,1);
  if (ready != 0) {
    if (*(void **)(work + 0x4c) != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap(*(void **)(work + 0x4c));
      *(u32 *)(work + 0x4c) = 0;
      CallVirtualHandlerSlot1((void *)(work + 0x18),0);
      FlushBufferAndRunCallback((void *)(work + 0x18));
      DestroyFndObjectList(work + 0x18);
    }
    TrophyPopup_ClearFlags(work,1);
  }
  screen = G2S_GetBG2ScrPtr();
  MIi_CpuClearFast(0,screen,0x800);
}
