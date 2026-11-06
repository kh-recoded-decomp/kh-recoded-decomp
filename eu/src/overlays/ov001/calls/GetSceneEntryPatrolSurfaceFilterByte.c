#include "nitro/types.h"

extern unsigned int *gFieldSceneEntryContext;

int GetSceneEntryPatrolSurfaceFilterByte(int groupIndex,int entryIndex) {
  return (int)*(char *)(*(int *)(*(int *)(*gFieldSceneEntryContext + groupIndex * 4 + 8) + 0x20) +
                       entryIndex * 8);
}
