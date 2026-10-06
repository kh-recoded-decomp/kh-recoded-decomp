#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 RuntimeState_SetObjectId();
extern u32 IsEntryFlagSet_020c01a0();
extern u32 func_ov103_020c032c();

void func_ov103_020becc4(u32 *work) {
  int ready;
  u32 selection;

  ready = func_ov103_020c032c();
  if (ready != 3) {
    return;
  }
  selection = *work;
  ready = IsEntryFlagSet_020c01a0(0,selection);
  if (ready == 0) {
    return;
  }
  PlaySoundEffect(0,1);
  RuntimeState_SetObjectId(selection);
  StartSubScene(0xffffffff,0xffffffff,1);
}
