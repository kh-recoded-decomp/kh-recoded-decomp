#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageCaption.h"

const u32 data_ov041_020cf8b4[5] = {
    0x000000E0, 0x00000020, 0x00000020, 0x00000020,
    0x000001A0,
};

const StageTextFrame gStageCaptionFrame = {
    1, 1, 30, 2, 0x3b4, 0xf, 0, 0,
};

const StageScaleFactors gStageScaleFactors = {
    {0x19a, 0x266, 0x333},
};
