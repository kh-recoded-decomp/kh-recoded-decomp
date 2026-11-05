#include "nitro/types.h"

extern u32 data_ov001_020a04f8;

u32 GetFieldObjectShadowModel(void) {
  return *(u32 *)(data_ov001_020a04f8 + 0x11c);
}
