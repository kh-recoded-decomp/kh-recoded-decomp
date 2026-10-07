#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void SetStageObjectRotation(s16 objectIndex, s32 rotationDegrees);

void SetStageObjectRotationIfServiceActive(s16 objectIndex, s32 rotationDegrees)
{
    if (g_stageEventsState != -1) {
        SetStageObjectRotation(objectIndex, rotationDegrees);
    }
}
