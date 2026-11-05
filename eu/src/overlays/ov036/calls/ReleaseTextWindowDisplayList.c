#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 Obj_Release();
extern u32 Slot_UnlinkAll();

void ReleaseTextWindowDisplayList(void) {
  Slot_UnlinkAll(gTextWindowResourceTable + 0x18);
  Obj_Release(gTextWindowResourceTable + 0x18);
}
