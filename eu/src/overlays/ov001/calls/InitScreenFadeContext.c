/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The task runner consumes native 32-bit callback words; zero retains its current state. */
extern unsigned int SelectScreenFadeHandler(void);

extern unsigned int *gFieldScreenTransitionWork;
extern unsigned int sOv001_BaTrTr_0209eb20;
extern unsigned int LoadCenteredScreenSprite();
extern unsigned int Msg_OpenContainerAndReadHeader();
extern unsigned int GetRunningTaskWork();
extern unsigned int MIi_CpuClearFast();

unsigned int InitScreenFadeContext(int *initialValues) {
  void *resource;
  int variant;

  variant = *initialValues;
  gFieldScreenTransitionWork = GetRunningTaskWork();
  MIi_CpuClearFast(0,gFieldScreenTransitionWork,0x68);
  *gFieldScreenTransitionWork = 0;
  gFieldScreenTransitionWork[6] = 0x1f000;
  gFieldScreenTransitionWork[1] = 0x2000;
  *(u8 *)(gFieldScreenTransitionWork + 0x19) = 0;
  gFieldScreenTransitionWork[10] = 0;
  gFieldScreenTransitionWork[0xb] = 0;
  gFieldScreenTransitionWork[7] = 0x1800;
  *(u8 *)((int)gFieldScreenTransitionWork + 0x66) = *(u8 *)((int)gFieldScreenTransitionWork + 0x66) & ~1U;
  resource = Msg_OpenContainerAndReadHeader(&sOv001_BaTrTr_0209eb20,2,0);
  gFieldScreenTransitionWork[0x18] = resource;
  LoadCenteredScreenSprite(variant);
  return (unsigned int)SelectScreenFadeHandler;
}
