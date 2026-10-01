#include "nitro/types.h"

extern unsigned int data_ov095_020c28c0;
extern unsigned int CopyClippedScreenRegion_020167d0();
extern unsigned int G2_GetBG3ScrPtr_02006f80();

void func_ov095_020c1608(void) {
  int work;
  void *pScreenDst;
  u16 *screen;

  work = data_ov095_020c28c0;
  pScreenDst = G2_GetBG3ScrPtr_02006f80();
  if (*(int *)(work + 0x11100) == 1) {
    if (*(int *)(work + 0x11104) == 1) {
      screen = *(u16 **)(work + 0x154);
      CopyClippedScreenRegion_020167d0(pScreenDst,screen,0,0,0,0,(u32)*screen >> 3,(u32)screen[1] >> 3,0x20,0x13);
      *(unsigned int *)(work + 0x11104) = 2;
    }
    return;
  }
  if (*(int *)(work + 0x11104) == 2) {
    screen = *(u16 **)(work + 0x144);
    CopyClippedScreenRegion_020167d0(pScreenDst,screen,0,0,0,0,(u32)*screen >> 3,(u32)screen[1] >> 3,0x20,0x13);
    *(unsigned int *)(work + 0x11104) = 1;
  }
}
