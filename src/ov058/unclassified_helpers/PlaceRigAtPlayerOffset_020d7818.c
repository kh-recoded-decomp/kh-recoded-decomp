#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 offsets[3];
} RigOffsetTable;

typedef struct {
    u16 flags;
    u8 pad_002[0x7c - 0x2];
    u16 angle;
    u8 pad_07e[0xa4 - 0x7e];
    VecFx32 position;
} EmitterRig;

extern const RigOffsetTable data_ov058_020d89b4;

extern int GetBoundedEntryField_0206db5c(int index);
extern VecFx32 *func_ov052_020ceb54(int entity);
extern u16 GetLinkedAngleOffset_020ceb7c(int entity);
extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, int angle, const VecFx32 *offset);

void PlaceRigAtPlayerOffset_020d7818(EmitterRig *rig, int index)
{
    VecFx32 pos;
    RigOffsetTable table = data_ov058_020d89b4;
    int entity = GetBoundedEntryField_0206db5c(index);
    u16 angle;

    pos = *func_ov052_020ceb54(entity);
    angle = GetLinkedAngleOffset_020ceb7c(entity) + 0x8000;

    RotateOffsetAroundY_020a9160(&pos, &pos, angle, &table.offsets[index]);
    rig->position = pos;
    rig->angle = angle;
    rig->flags |= 0x20;
}
