#include "nitro/types.h"

extern u32 data_0205fe0c;
extern u32 ComputePlayerStats_02050b30();
extern u32 GetOverlaySelectionRecord();

void func_0204f840(void) {
  void *out;

  out = GetOverlaySelectionRecord(0);
  ComputePlayerStats_02050b30(data_0205fe0c,out,0,1);
}
