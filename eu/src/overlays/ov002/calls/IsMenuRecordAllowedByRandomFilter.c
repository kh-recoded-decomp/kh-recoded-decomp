#include "nitro/types.h"

extern unsigned char gMenuRandomRecordExclusions;

unsigned int IsMenuRecordAllowedByRandomFilter(int value) {
  int index;

  index = 0;
  do {
    if (value == *(int *)(&gMenuRandomRecordExclusions + index * 4)) {
      return 0;
    }
    index = index + 1;
  } while (index < 0x13);
  return 1;
}
