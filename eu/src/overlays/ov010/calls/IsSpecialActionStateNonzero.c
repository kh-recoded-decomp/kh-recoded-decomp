#include "nitro/types.h"

extern int *gSpecialActionWork;

int IsSpecialActionStateNonzero(void) {
  if (gSpecialActionWork == (int *)0x0) {
    return 0;
  }
  if (*gSpecialActionWork != 0) {
    return 1;
  }
  return 0;
}
