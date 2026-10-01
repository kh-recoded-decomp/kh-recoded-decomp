#include "nitro/types.h"

extern u32 PlaySoundEffect_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc8a0();
extern u32 func_ov079_020c4800();

void func_ov079_020c4bec(u32 work) {
  PlaySoundEffect_0204d924(0,3);
  func_ov079_020c4800(work);
  func_ov039_020bc8a0();
  func_ov039_020bbf78(0,0xffffffff,0);
}
