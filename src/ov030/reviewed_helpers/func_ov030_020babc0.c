#include "nitro/types.h"

extern unsigned int data_ov030_020bd000;

BOOL func_ov030_020babc0(void) {
  if (data_ov030_020bd000 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov030_020bd000 + 6) & 1) == 0;
}
