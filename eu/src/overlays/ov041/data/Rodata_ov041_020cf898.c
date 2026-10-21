#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageCaption.h"

const StageCaptionFrameTiles gStageCaptionFrameTiles = {
    {0xe0, 0x20, 0x20, 0x20, 0x1a0},
};

const StageTextFrame gStageCaptionFrame = {
    1, 1, 30, 2, 0x3b4, 0xf, 0, 0,
};

const StageScaleFactors gStageScaleFactors = {
    {0x19a, 0x266, 0x333},
};
