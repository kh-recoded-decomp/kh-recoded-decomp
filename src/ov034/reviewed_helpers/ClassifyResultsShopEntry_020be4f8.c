#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])

u32 ClassifyResultsShopEntry_020be4f8(int itemIndex)

{
  int reservedCount;
  
  if (0 < *(int *)(resultsWork + 0x6d6c)) {
    reservedCount = 2;
    if (*(int *)(resultsWork + 0x6d70) <= 0) {
      reservedCount = 1;
    }
    if (itemIndex == *(int *)(resultsWork + 0x6d64) - reservedCount) {
      return 2;
    }
  }
  if ((0 < *(int *)(resultsWork + 0x6d70)) && (itemIndex == *(int *)(resultsWork + 0x6d64) + -1)) {
    return 1;
  }
  return 0;
}
