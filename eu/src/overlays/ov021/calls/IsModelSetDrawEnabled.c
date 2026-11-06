#include "nitro/types.h"

BOOL IsModelSetDrawEnabled(u32 *flags) {
  if ((*flags & 1) == 0) {
    return FALSE;
  }
  return (*flags & 2) != 0;
}
