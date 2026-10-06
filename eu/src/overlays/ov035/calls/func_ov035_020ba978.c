#include "nitro/types.h"

extern unsigned int data_ov035_020bc500;

BOOL func_ov035_020ba978(void) {
  if (data_ov035_020bc500 == 0) {
    return FALSE;
  }
  return (*(u16 *)(data_ov035_020bc500 + 6) & 1) == 0;
}
