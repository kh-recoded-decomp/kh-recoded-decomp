#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DirectionEntry {
    s16 x;
    s16 y;
    s16 z;
} DirectionEntry;

typedef struct DirectionTableBlock {
    u8 pad_00[4];
    DirectionEntry directions[8];
} DirectionTableBlock;

typedef struct FacingObject {
    u8 pad_00[0x3a];
    u8 directionIndex;
    u8 pad_3b[5];
    VecFx32 position;
} FacingObject;

typedef struct FacingQuery {
    u8 pad_00[0x0c];
    u8 playerId;
} FacingQuery;

extern const DirectionTableBlock sOv006ElevatorFrameData;
extern VecFx32 *func_ov001_0206dc4c(int playerId);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL IsPlayerInFacingHalfPlane(FacingObject *object, FacingQuery *query)
{
    VecFx32 facing;
    VecFx32 toTarget;
    int index = object->directionIndex - 1;

    facing.x = sOv006ElevatorFrameData.directions[index].x;
    facing.y = sOv006ElevatorFrameData.directions[index].y;
    facing.z = sOv006ElevatorFrameData.directions[index].z;
    VEC_Subtract(func_ov001_0206dc4c(query->playerId), &object->position, &toTarget);
    toTarget.y = 0;
    VEC_Normalize(&toTarget, &toTarget);
    return VEC_DotProduct(&facing, &toTarget) >= 0;
}
