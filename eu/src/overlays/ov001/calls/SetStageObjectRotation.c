#include "nitro/types.h"
#include "src/overlays/ov001/StageObjectHandle.h"

extern StageObjectHandle *GetStageObjectHandle(u32 id);

void SetStageObjectRotation(int objectIndex, u32 rotationDegrees)
{
    StageObjectHandle *object;

    object = GetStageObjectHandle((objectIndex + 1U) & 0xffff);
    object->rotationDegrees = rotationDegrees;
}
