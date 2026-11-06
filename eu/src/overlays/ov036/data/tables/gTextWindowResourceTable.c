#include "nitro/types.h"

extern u8 gTextWindowStaticWorkPrefix[];

void *gTextWindowResourceTable[1] = {
    gTextWindowStaticWorkPrefix,
};
