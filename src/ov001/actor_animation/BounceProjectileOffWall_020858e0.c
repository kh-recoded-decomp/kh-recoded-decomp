#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x28];
} ShapeStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    u32 words[0x18];
} CollisionQuery;

typedef struct ContactRef {
    void *owner;
    s32 type;
} ContactRef;

typedef struct ProjectileBody {
    u8 pad_00[0x10];
    u8 anchor[1];
} ProjectileBody;

typedef struct Projectile {
    u8 pad_00[0xc];
    ProjectileBody *body;
    u8 pad_10[4];
    void (*update)(struct Projectile *self);
    u8 pad_18[0x40 - 0x18];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    s32 state;
    u8 pad_5c[0x70 - 0x5c];
    VecFx32 drift;
    VecFx32 velocity;
    s32 heading;
    u8 pad_8c[4];
    s32 baseAngle;
    s32 turn;
    u8 pad_98[4];
    s32 timer;
} Projectile;

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern CollisionShape func_0203adcc(ShapeStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void SetShapePosition_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern BOOL SweepWorldCollisionPreserveState_020364bc(CollisionQuery *query);
extern int FX_Atan2_02006124(fx32 y, fx32 x);
extern void SpawnSoundSlot_0204da8c(int soundId, int mode, const VecFx32 *position, int flags);
extern int FixedPointMultiply12(int left, int right);
extern void func_ov001_02085138(Projectile *self);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + (FX32_ONE >> 1)) >> 12))

static inline void BuildSegmentShape(CollisionShape *shape, ShapeStorage *storage, const VecFx32 *position, const VecFx32 *top)
{
    VecFx32 axis;
    VecFx32 delta;
    fx32 length;
    VEC_Subtract_01ff9e3c(top, position, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    *shape = func_0203adcc(storage, position, top, &axis, length);
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 CrossProduct(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    result.x = -FX_MUL(a->z, b->y);
    result.y = 0;
    result.z = FX_MUL(a->x, b->y);
    return result;
}

void BounceProjectileOffWall_020858e0(ContactRef *contact, const VecFx32 *normal, Projectile *projectile)
{
    BOOL bounce = TRUE;

    if (contact->type == 2 && VEC_DotProduct_01ff9e6c(&projectile->velocity, normal) < -0xb50 && projectile->state == 1) {
        QueryWorkspace workspace;
        CollisionQuery sweep;
        CollisionQuery query;
        ShapeStorage storage;
        CollisionShape shape;
        VecFx32 side;
        VecFx32 top;
        VecFx32 up;
        VecFx32 position;
        u8 i;

        projectile->drift = MakeVec(0, 0x266, 0);
        projectile->state = 2;
        projectile->update = func_ov001_02085138;
        projectile->timer = 0;
        top = MakeVec(0, -0x3000, 0);
        BuildSegmentShape(&shape, &storage, &data_02053438, &top);
        CollisionQuery_Init_02034c74(&query, 0, projectile->body->anchor, 1, 2, 0, &shape, &workspace, NULL);
        sweep = query;
        up = MakeVec(0, FX32_ONE, 0);
        side = CrossProduct(normal, &up);
        if (side.z < 0) {
            NegateVecFx32_0204aa40(&side);
        }
        func_01ffaff4(&side, &side);
        ScaleVecFx32InPlace_0204a5e4(&side, 0x3e67);
        for (i = 0; i < 2; i++) {
            if (i == 1) {
                NegateVecFx32_0204aa40(&side);
            }
            position = AddVec(&projectile->position, &side);
            SetShapePosition_0203afa0(&shape, &position);
            if (SweepWorldCollisionPreserveState_020364bc(&sweep)) {
                int index;

                VEC_Normalize_01ff9f88(&side, &projectile->velocity);
                projectile->baseAngle = projectile->heading;
                projectile->turn = FX_Atan2_02006124(projectile->velocity.z, projectile->velocity.x);
                projectile->turn = projectile->turn - projectile->baseAngle;
                index = (s32)((((s64)projectile->turn << 16) / 0x6488) & 0xffff) >> 4;
                projectile->turn = FX_Atan2_02006124(data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
                projectile->turn = projectile->turn + projectile->baseAngle;
                SpawnSoundSlot_0204da8c(0x1a1, 1, &projectile->position, 0);
                break;
            }
        }
        bounce = FALSE;
    }
    if (bounce) {
        fx32 dot = VEC_DotProduct_01ff9e6c(&projectile->drift, normal);
        VEC_MultAdd_01ffa09c(-(dot + FixedPointMultiply12(dot, 0xccd)), normal, &projectile->drift, &projectile->drift);
    }
}





