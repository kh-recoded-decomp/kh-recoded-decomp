#include "nitro/types.h"

extern unsigned int data_ov030_020bd020;

BOOL func_ov030_020babe0(void) {
  if (data_ov030_020bd020 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov030_020bd020 + 6) & 1) == 0;
}
