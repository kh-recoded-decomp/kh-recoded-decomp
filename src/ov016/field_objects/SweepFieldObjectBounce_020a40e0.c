#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x50];
    void (*callback)(void);
    void *context;
    u8 pad_58[8];
} SweepQuery;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u8 data[0x20];
} SweepShape;

typedef struct {
    u8 data[0x10];
} ShapeExtent;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x60 - 0x44];
    fx32 travelled;
    u8 pad_64[0xc0 - 0x64];
    u32 flags;
    u8 pad_c4[0xd0 - 0xc4];
    fx32 distance;
} FieldObject;

extern void *func_02036240(u32 actorId);
extern void func_0203ad14(SweepShape *shape, ShapeExtent *extent, VecFx32 *center, fx32 radius);
extern void CollisionQuery_Init_02034c74(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, s32 unk44);
extern void *SweepWorldCollision_020364a0(SweepQuery *query);
extern void func_ov016_020a3d90(void);
extern void func_ov016_020a2c44(FieldObject *obj);
extern void EnterFieldUnitPhase6_020a29a4(FieldObject *obj);

int SweepFieldObjectBounce_020a40e0(FieldObject *obj)
{
    fx32 range;
    fx32 half;
    fx32 travel;
    fx32 radius;
    void *actor;
    SweepQuery query;
    QueryWorkspace workspace;
    VecFx32 center;
    SweepShape shape;
    ShapeExtent extent;

    if (obj->flags & 0x8000) {
        range = obj->distance - 0xf000;
        actor = func_02036240(obj->actorId);
        center = obj->position;
        travel = obj->travelled;
        center.y += 0xc00;
        if (travel >= range) {
            travel = range;
        }
        half = range / 2;
        if (half > travel) {
            radius = (s64)travel * 0x4800 / half;
        } else {
            travel -= half;
            radius = (s64)(half - travel) * 0x4800 / half;
        }
        func_0203ad14(&shape, &extent, &center, radius);
        CollisionQuery_Init_02034c74(&query, 0, actor, 8, 0, 0, &shape, &workspace, 0);
        query.context = obj;
        query.callback = func_ov016_020a3d90;
        SweepWorldCollision_020364a0(&query);
    }
    func_ov016_020a2c44(obj);
    if (!(obj->flags & 0x8020)) {
        EnterFieldUnitPhase6_020a29a4(obj);
    }
    return 0;
}
