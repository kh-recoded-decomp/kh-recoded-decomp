#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void data_ov041_020cedcc(StageCaption *caption);
extern void StageCaptionState1Noop(StageCaption *caption);
extern void StageCaptionState2(StageCaption *caption);
extern void StageCaptionState3Noop(StageCaption *caption);
extern void data_ov041_020ceee4(StageCaption *caption);
extern void StageCaptionState5Noop(StageCaption *caption);

/* What the caption does each frame in each of its states. */
void (*gStageCaptionStates[6])(StageCaption *caption) = {
    data_ov041_020cedcc,
    StageCaptionState1Noop,
    StageCaptionState2,
    StageCaptionState3Noop,
    data_ov041_020ceee4,
    StageCaptionState5Noop,
};
