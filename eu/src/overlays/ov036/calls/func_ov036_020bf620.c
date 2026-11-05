#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 UpdateDisplayObjectListQueued();

void func_ov036_020bf620(void) {
  UpdateDisplayObjectListQueued(gTextWindowResourceTable + 0x18);
}
