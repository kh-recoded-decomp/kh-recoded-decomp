#include "nitro/types.h"

extern unsigned int data_ov031_020bc800;

BOOL func_ov031_020bb48c(void) {
  if (data_ov031_020bc800 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov031_020bc800 + 6) & 1) == 0;
}
