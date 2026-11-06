#include "nitro/types.h"

extern u16 gPadPressedStorage;
extern u32 gTrophyPopupWorkStorage;
extern u32 PlaySoundEffect();
extern u32 GetMenuInputState();
extern u32 SetPopupSlotVisible_020c319c();
extern u32 StateMachine_SetState();

void WaitForPopupDismiss(u32 context)

{
  int result;

  result = GetMenuInputState();
  if (((((gPadPressedStorage & 1) == 0) && ((gPadPressedStorage & 2) == 0)) && ((gPadPressedStorage & 8) == 0))
     && ((*(u16 *)(result + 8) & 3) != 1)) {
    return;
  }
  SetPopupSlotVisible_020c319c(*(u32 *)(gTrophyPopupWorkStorage + 0x10),0);
  PlaySoundEffect(0,1);
  StateMachine_SetState(context,6);
  return;
}
