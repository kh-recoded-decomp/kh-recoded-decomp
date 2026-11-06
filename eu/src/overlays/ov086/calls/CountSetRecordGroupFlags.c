#include "nitro/types.h"

extern unsigned char gRecordGroupEntryCountsHead;
extern unsigned int IsSessionFlagSet();

int CountSetRecordGroupFlags(int group) {
  int flag;
  int countOrIndex;
  int baseIndex;
  int unlocked;
  int offsetOrIndex;

  baseIndex = 0;
  unlocked = 0;
  countOrIndex = 0;
  if (0 < group) {
    do {
      offsetOrIndex = countOrIndex * 4;
      countOrIndex = countOrIndex + 1;
      baseIndex = baseIndex + *(int *)(&gRecordGroupEntryCountsHead + offsetOrIndex);
    } while (countOrIndex < group);
  }
  offsetOrIndex = 0;
  countOrIndex = *(int *)(&gRecordGroupEntryCountsHead + group * 4);
  if (0 < countOrIndex) {
    do {
      flag = IsSessionFlagSet(baseIndex + offsetOrIndex + 0x581);
      offsetOrIndex = offsetOrIndex + 1;
      if (flag != 0) {
        unlocked = unlocked + 1;
      }
    } while (offsetOrIndex < countOrIndex);
  }
  return unlocked;
}
