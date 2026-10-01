#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])
extern u32 func_02025438();
extern u32 func_ov001_02063620();
extern u32 func_ov034_020bb304();

u32 StartResultsScreen_020bdbd0(void)

{
  u16 statusFlags;
  int work;
  int status;
  
  work = resultsWork;
  status = func_ov001_02063620();
  if (status != 0) {
    return 0xffffffff;
  }
  func_02025438(0);
  func_ov034_020bb304();
  statusFlags = *(u16 *)(work + 6);
  if ((statusFlags & 1) != 0) {
    *(u16 *)(work + 6) = statusFlags & 0xfffe;
  }
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) | 0x8000;
  return 1;
}
