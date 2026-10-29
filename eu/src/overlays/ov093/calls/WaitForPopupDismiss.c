#include "nitro/types.h"

extern u16 data_02060500;
extern u32 data_ov093_020c5104;
extern u32 PlaySoundEffect();
extern u32 GetMenuInputState();
extern u32 SetPopupSlotVisible_020c319c();
extern u32 StateMachine_SetState();

void WaitForPopupDismiss(u32 context)

{
  int result;

  result = GetMenuInputState();
  if (((((data_02060500 & 1) == 0) && ((data_02060500 & 2) == 0)) && ((data_02060500 & 8) == 0))
     && ((*(u16 *)(result + 8) & 3) != 1)) {
    return;
  }
  SetPopupSlotVisible_020c319c(*(u32 *)(data_ov093_020c5104 + 0x10),0);
  PlaySoundEffect(0,1);
  StateMachine_SetState(context,6);
  return;
}
