#include "nitro/types.h"

extern u8 data_ov041_020cedcc[];
extern u8 StageCaptionState0Noop[];
extern u8 data_ov041_020cee9c[];
extern u8 StageCaptionState1Noop[];
extern u8 data_ov041_020ceee4[];
extern u8 StageCaptionState2Noop[];

void *gOv041ResourceSets[6] = {
    data_ov041_020cedcc,
    StageCaptionState0Noop,
    data_ov041_020cee9c,
    StageCaptionState1Noop,
    data_ov041_020ceee4,
    StageCaptionState2Noop,
};
