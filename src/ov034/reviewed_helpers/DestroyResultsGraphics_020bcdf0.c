#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])
extern u32 DestroyFndObjectList_020014f0();
extern u32 FreePointerIfSet_020ba294();
extern u32 NotifyBothOrOne_02001154();
extern u32 func_02001474();
extern u32 func_02051dfc();
extern u32 func_ov027_020b7dfc();
extern u32 func_ov027_020b8c58();

void DestroyResultsGraphics_020bcdf0(void)

{
  NotifyBothOrOne_02001154(1,0x20c0ef0,0);
  func_02051dfc(0);
  FreePointerIfSet_020ba294((void *)(resultsWork + 0x6b3c));
  DestroyFndObjectList_020014f0(resultsWork + 0x6b60);
  func_02001474(resultsWork + 0x6b48);
  func_02001474(resultsWork + 0x6b54);
  func_ov027_020b7dfc(resultsWork + 0x10);
  func_ov027_020b8c58(resultsWork + 0x5c);
  return;
}
