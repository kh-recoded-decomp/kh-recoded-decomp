#include "nitro/types.h"

extern void func_ov099_020bf818(int mode, u8 *work);
extern void PlaySoundEffect_0204d924(int channel, int sound);

void CloseSubBgPanel_020bf0dc(u8 *work) {
  u32 offset;

  if (*(int *)(work + 0xcf0c) != 1) {
    return;
  }
  *(int *)(work + 0xcf0c) = 0;
  offset = 0;
  if (*(int *)(work + 0xcf0c) == 1) {
    offset = 0x100;
  }
  *(vu32 *)0x04001018 = offset & 0x1ff;
  func_ov099_020bf818(1, work);
  PlaySoundEffect_0204d924(0, 2);
}
