#include "nitro/types.h"

extern unsigned int data_ov035_020bc4e0;

BOOL func_ov035_020ba958(void) {
  if (data_ov035_020bc4e0 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov035_020bc4e0 + 6) & 1) == 0;
}
