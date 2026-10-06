#include "nitro/types.h"

BOOL func_ov021_020a9d24(u32 *flags) {
  if ((*flags & 1) == 0) {
    return FALSE;
  }
  return (*flags & 2) != 0;
}
