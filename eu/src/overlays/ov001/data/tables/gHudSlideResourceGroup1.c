#include "nitro/types.h"

extern u16 gModeCaptionGlyph03B7[];
extern u32 gHudSlideResourceGroup1Descriptor[];
extern u16 gModeCaptionGlyph03B9[];

void *gHudSlideResourceGroup1[3] = {
    gModeCaptionGlyph03B7,
    gHudSlideResourceGroup1Descriptor,
    gModeCaptionGlyph03B9,
};
