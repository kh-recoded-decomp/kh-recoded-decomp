#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitArrowPromptWork(void);
extern void ReleaseArrowPromptWork(void);

StageManagerTaskDescriptor gFieldHudExtraTaskDescriptor = {
    0x000e0013,
    (void *)InitArrowPromptWork,
    (void *)ReleaseArrowPromptWork,
    0x4c,
    NULL,
};
