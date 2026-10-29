#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PushStackEntry();

void SelectMenu_ConfirmSelection(u8 *selection) {
  PushStackEntry(*selection);
  StartSubScene(8,0xffffffff,1);
  PlaySoundEffect(0,1);
}
