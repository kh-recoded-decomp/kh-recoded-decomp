#include "nitro/types.h"

extern unsigned int data_ov035_020bc4e0;
extern unsigned int ActorRegistry_ForEachCallback_020360a0();
extern unsigned int AdvanceLoopingAnimation_020bdb0c();
extern unsigned int StageManager_Update_02087694();
extern unsigned int UpdatePrizeOrbs_020668e4();
extern unsigned int func_020bd15c();
extern unsigned int func_ov001_02067d80();
extern unsigned int func_ov001_0206d95c();
extern unsigned int func_ov001_0206dc38();
extern unsigned int func_ov001_0207ecc4();
extern unsigned int func_ov035_020bae64();
extern unsigned int func_ov035_020bae74();
extern unsigned int func_ov035_020bb670();

void func_ov035_020ba7dc(int paused) {
  int result;
  u32 step;
  int work;

  work = data_ov035_020bc4e0;
  if ((*(u16 *)(data_ov035_020bc4e0 + 0x24) & 0x100) != 0) {
    AdvanceLoopingAnimation_020bdb0c(0x1000);
  }
  if (paused == 0) {
    if ((*(u16 *)(work + 0x24) & 1) != 0) {
      func_ov001_02067d80(0x1000);
    }
    if ((*(u16 *)(work + 0x24) & 2) != 0) {
      func_ov001_0207ecc4(0x1000);
    }
    if ((*(u16 *)(work + 0x24) & 4) != 0) {
      result = func_ov035_020bae64();
      func_ov035_020bb670(result,0x1000);
    }
  }
  step = func_ov001_0206dc38();
  if (0 < (int)step) {
    if ((*(u16 *)(work + 0x24) & 8) != 0) {
      func_ov001_0206d95c(0x1000);
    }
  }
  if (paused == 0) {
    step = 0x1000;
    result = func_ov035_020bae74();
    if ((result != 0) || ((*(u16 *)(work + 0x24) & 0x10) == 0)) {
      step = 0;
    }
    StageManager_Update_02087694(step);
    if ((*(u16 *)(work + 0x24) & 0x20) != 0) {
      UpdatePrizeOrbs_020668e4();
    }
  }
  if ((*(u16 *)(work + 0x24) & 0x40) != 0) {
    ActorRegistry_ForEachCallback_020360a0((void *)0x1000);
  }
  work = func_ov035_020bae74();
  if (work != 0) {
    func_020bd15c(*(unsigned int *)(*(int *)(data_ov035_020bc4e0 + 0xb8) + 9000));
  }
}
