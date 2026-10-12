#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitContextForMode(void);
extern void DispatchByContextMode(void);

StageManagerTaskDescriptor gSceneMinigameTaskDescriptor = {
    0x000e0013,
    (void *)InitContextForMode,
    (void *)DispatchByContextMode,
    0xb4,
    NULL,
};
