#include "nitro/types.h"

unsigned int func_ov046_020c2ad8(int work) {
  BOOL allowedKind;
  unsigned int result;

  result = 0;
  if (*(int *)(work + 0xf4) == 0) {
    allowedKind = TRUE;
    if ((*(int *)(work + 0xe4) != 0x13) && (*(int *)(work + 0xe4) != 0x15)) {
      allowedKind = FALSE;
    }
    if (allowedKind) {
      result = 1;
    }
  }
  return result;
}
