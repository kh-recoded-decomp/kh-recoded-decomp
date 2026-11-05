#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 UpdateDisplayObjectListQueued();

void UpdateTextWindowDisplayList(void) {
  UpdateDisplayObjectListQueued(gTextWindowResourceTable + 0x18);
}
