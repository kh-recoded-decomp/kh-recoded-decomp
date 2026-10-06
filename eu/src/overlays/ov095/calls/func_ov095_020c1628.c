#include "nitro/types.h"

extern unsigned int data_ov095_020c28e0;
extern unsigned int NNS_G2dBGLoadScreenRect();
extern unsigned int G2_GetBG3ScrPtr();

void func_ov095_020c1628(void) {
  int work;
  void *pScreenDst;
  u16 *screen;

  work = data_ov095_020c28e0;
  pScreenDst = G2_GetBG3ScrPtr();
  if (*(int *)(work + 0x11100) == 1) {
    if (*(int *)(work + 0x11104) == 1) {
      screen = *(u16 **)(work + 0x154);
      NNS_G2dBGLoadScreenRect(pScreenDst,screen,0,0,0,0,(u32)*screen >> 3,(u32)screen[1] >> 3,0x20,0x13);
      *(unsigned int *)(work + 0x11104) = 2;
    }
    return;
  }
  if (*(int *)(work + 0x11104) == 2) {
    screen = *(u16 **)(work + 0x144);
    NNS_G2dBGLoadScreenRect(pScreenDst,screen,0,0,0,0,(u32)*screen >> 3,(u32)screen[1] >> 3,0x20,0x13);
    *(unsigned int *)(work + 0x11104) = 1;
  }
}
