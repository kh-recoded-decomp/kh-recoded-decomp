#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    VecFx32 base;
    VecFx32 top;
    VecFx32 axis;
    fx32 radius;
} AxisCylinder;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    u32 words[0x18];
} CollisionQuery;

typedef struct {
    VecFx32 offsets[3];
} OffsetTable;

typedef struct {
    u8 kind;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flagA;
    u8 flagB;
    u8 pad_26[6];
} EffectParams;

typedef struct {
    u8 pad_00[2];
    u16 locked;
} EnemyStats;

typedef struct {
    u8 pad_00[0x14];
    s32 timer;
    u8 pad_18[0x12];
    s16 effectHandle;
} AiState;

typedef struct Enemy Enemy;
typedef void (*EnemyNotify)(Enemy *enemy, int value);
typedef void (*EnemyTurn)(Enemy *enemy, u16 angle);

struct Enemy {
    u8 pad_000[0x1d4];
    EnemyStats *stats;
    u8 pad_1d8[0x210 - 0x1d8];
    EnemyTurn onTurn;
    u8 pad_214[0x230 - 0x214];
    void *model;
    u8 pad_234[0x9ac - 0x234];
    u64 stateFlags;
    u8 side;
    u8 pad_9b5[0xa0c - 0x9b5];
    fx32 height;
    u8 pad_a10[0x10ec - 0xa10];
    EnemyNotify onNotify;
    u8 pad_10f0[0x1258 - 0x10f0];
    AiState ai;
};

extern const s16 data_0205356c[];
extern const OffsetTable data_ov058_020d8970;

extern int func_ov001_0206db8c(int index);
extern BOOL IsGroupMemberActive_020a8d1c(int groupId, int index);
extern fx32 func_ov001_0206db44(void);
extern void *GetBoundedEntryField_0206db5c(int index);
extern VecFx32 *func_ov052_020ceb54(void *actor);
extern u16 GetLinkedAngleOffset_020ceb7c(void *actor);
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape_0203aeac(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern CollisionShape InitAxisCylinderShape_0203adcc(AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top, const VecFx32 *axis, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void func_ov021_020a8ab4(EffectParams *params);
extern s16 func_ov021_020a8ca0(EffectParams *params, int group);
extern void ResetEnemyLaunchState_020d6a78(Enemy *enemy);

void SnapEnemyBesidePlayer_020d5468(Enemy *enemy)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    SweptShape swept;
    CollisionQuery bodyQuery;
    CollisionQuery groundQuery;
    VecFx32 target;
    VecFx32 delta;
    VecFx32 offset;
    MtxFx33 facing;
    CollisionShape shapeCopy;
    AxisCylinder axisCylinder;
    CylinderStorage cylinder;
    VecFx32 start;
    VecFx32 end;
    VecFx32 motion;
    MtxFx33 turn;
    OffsetTable offsets;
    EffectParams params;
    VecFx32 axis1;
    VecFx32 diff1;
    CollisionShape shape1;
    CollisionShape shape2;
    VecFx32 diff2;
    VecFx32 axis2;
    OffsetTable table;
    VecFx32 point;
    AiState *ai = &enemy->ai;
    void *player;
    VecFx32 *playerPos;
    int angle;
    int index;
    fx32 timer;
    int i;
    BOOL placed = FALSE;

    if (enemy->stateFlags & 0x20) {
        return;
    }
    if (ai->effectHandle != -1) {
        if (IsGroupMemberActive_020a8d1c(func_ov001_0206db8c(7), ai->effectHandle)) {
            return;
        }
        ai->effectHandle = -1;
    }
    timer = ai->timer + func_ov001_0206db44();
    ai->timer = timer;
    if (timer < 0x1e000) {
        return;
    }
    player = GetBoundedEntryField_0206db5c(0);
    playerPos = func_ov052_020ceb54(player);
    angle = GetLinkedAngleOffset_020ceb7c(player);
    if (enemy->onTurn != NULL) {
        enemy->onTurn(enemy, angle);
    }
    MTX_Identity33_01ff90ec(&facing);
    index = (u16)(angle + ((ai->timer - 0x1e000) >> 12)) >> 4;
    MTX_RotY33_01ff923c(&facing, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    table = data_ov058_020d8970;
    for (i = 0; i < 4 && placed != TRUE; i++) {
        offsets = table;
        offset = offsets.offsets[enemy->side];
        MTX_Identity33_01ff90ec(&turn);
        switch (i) {
        case 0:
            break;
        case 1:
            MTX_RotY33_01ff923c(&turn, FX32_ONE, 0);
            break;
        case 2:
            MTX_RotY33_01ff923c(&turn, 0, -FX32_ONE);
            break;
        case 3:
            MTX_RotY33_01ff923c(&turn, -FX32_ONE, 0);
            break;
        }
        MTX_Concat33_01ff9270(&facing, &turn, &facing);
        MTX_MultVec33_01ff9404(&offset, &facing, &offset);
        VEC_Add_01ff9e0c(&offset, playerPos, &target);
        VEC_Subtract_01ff9e3c(&target, playerPos, &delta);
        end = *playerPos;
        start = end;
        end.y += enemy->height;
        ScaleVecFx32_01ffafb4(0x1800, &delta, &motion);
        VEC_Subtract_01ff9e3c(&end, &start, &diff1);
        axis1 = diff1;
        shape1 = InitCylinderShape_0203aeac(&cylinder, &start, &end, &axis1, func_01ffaff4(&axis1, &axis1), 0x900);
        swept.shape = shape1;
        swept.delta = motion;
        OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        sweptCopy = swept;
        CollisionQuery_Init_02034c74(&bodyQuery, 1, enemy->model, 0xe, 1, 1, &sweptCopy, &workspace, NULL);
        sweep = bodyQuery;
        if (SweepWorldCollision_020364a0(&sweep) == NULL) {
            point = target;
            end = point;
            start = point;
            start.y += enemy->height;
            end.y -= 0x2000;
            VEC_Subtract_01ff9e3c(&end, &start, &diff2);
            axis2 = diff2;
            shape2 = InitAxisCylinderShape_0203adcc(&axisCylinder, &start, &end, &axis2, func_01ffaff4(&axis2, &axis2));
            shapeCopy = shape2;
            CollisionQuery_Init_02034c74(&groundQuery, 0, enemy->model, 9, 1, 0, &shapeCopy, &workspace, NULL);
            sweep = groundQuery;
            if (SweepWorldCollision_020364a0(&sweep) != NULL) {
                target.y = ((AxisCylinder *)shapeCopy.data)->top.y;
                Obj_SetPosition_0203569c(enemy->model, &target);
                placed = TRUE;
            }
        }
    }
    if (!placed) {
        return;
    }
    func_ov021_020a8ab4(&params);
    params.kind = enemy->side;
    params.flagB = 0;
    params.flagA = 0;
    params.position = *func_ov052_020ceb54(enemy);
    func_ov021_020a8ca0(&params, func_ov001_0206db8c(7));
    ResetEnemyLaunchState_020d6a78(enemy);
    if (enemy->stats->locked != 0) {
        return;
    }
    enemy->onNotify(enemy, 0xf);
}
