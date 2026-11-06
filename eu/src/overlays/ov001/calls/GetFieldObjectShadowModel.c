#include "nitro/types.h"

extern u32 gFieldObjectClassManager;

u32 GetFieldObjectShadowModel(void) {
  return *(u32 *)(gFieldObjectClassManager + 0x11c);
}
