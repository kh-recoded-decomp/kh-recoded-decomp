#include "nitro/types.h"

extern unsigned int data_ov031_020bc820;

BOOL func_ov031_020bb4ac(void) {
  if (data_ov031_020bc820 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov031_020bc820 + 6) & 1) == 0;
}
