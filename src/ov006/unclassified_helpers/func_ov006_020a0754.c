#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} DirectionEntry;

typedef struct {
    u8 pad_00[0x04];
    DirectionEntry directions[8];
} DirectionTableBlock;

typedef struct {
    u8 pad_00[0x3a];
    u8 directionIndex;
    u8 pad_3b[0x05];
    VecFx32 position;
} FacingObject;

typedef struct {
    u8 pad_00[0x0c];
    u8 playerId;
} FacingQuery;

extern const DirectionTableBlock data_ov006_020a1834;
extern VecFx32 *func_ov001_0206dc4c(int playerId);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL func_ov006_020a0754(FacingObject *object, FacingQuery *query)
{
    VecFx32 facing;
    VecFx32 toTarget;
    int index = object->directionIndex - 1;

    facing.x = data_ov006_020a1834.directions[index].x;
    facing.y = data_ov006_020a1834.directions[index].y;
    facing.z = data_ov006_020a1834.directions[index].z;
    VEC_Subtract_01ff9e3c(func_ov001_0206dc4c(query->playerId), &object->position, &toTarget);
    toTarget.y = 0;
    func_01ff9f88(&toTarget, &toTarget);
    return VEC_DotProduct_01ff9e6c(&facing, &toTarget) >= 0;
}
