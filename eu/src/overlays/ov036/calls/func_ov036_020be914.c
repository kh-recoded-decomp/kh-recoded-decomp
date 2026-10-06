#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 FSi_DefaultStepDoneB();
extern u32 func_ov036_020beb3c();
extern u32 func_ov036_020bebbc();
extern u32 func_ov036_020bf4f4();

void func_ov036_020be914(void) {
  func_ov036_020bf4f4();
  func_ov036_020bebbc();
  func_ov036_020beb3c();
  FSi_DefaultStepDoneB(gTextWindowResourceTable + 0x6830);
  gTextWindowResourceTable = 0;
}
