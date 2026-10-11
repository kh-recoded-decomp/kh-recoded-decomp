#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x7c];
    u16 rotation;
    u8 pad_82[0x32];
    VecFx32 scale;
    u8 pad_c0[0x4c];
    u8 collision[4];
} ActorNode;

typedef struct {
    u16 flags;
    u8 pad_02[0x7a];
    u16 rotation;
    u8 pad_7e[0x32];
    VecFx32 scale;
} UnitModel;

typedef struct {
    u8 pad_00[0x60];
    UnitModel *models[17];
} UnitDesc;

typedef struct {
    u8 pad_00[4];
    UnitDesc *desc;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 pad_33[0x3d];
    u16 unk_70_0 : 7;
    u16 pose : 2;
    u16 unk_70_9 : 7;
    u8 pad_72[4];
    s8 visible;
    u8 kind;
    u8 pad_78[0x47];
    s8 savedVisible;
    u32 behaviorFlags;
    u8 pad_c4[8];
    VecFx32 motion;
    u32 moveFlags;
    u8 work[0x10];
} FieldUnit;

typedef struct {
    u8 pad_00[4];
    void **world;
} CollisionHost;

extern const VecFx32 data_02053438;

extern ActorNode *func_02036240(int actorId);
extern CollisionHost *func_02036230(void);
extern void func_02033c3c(void *world, void *collision);
extern void SetFieldObjectWeightByKind_020a29cc(FieldUnit *unit, int kind);
extern void func_ov001_02086434(FieldUnit *unit, int flag);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern u32 random_next_scaled_0202aa04(u32 range);
extern int nextRandom12_0202aa58(void);
extern void InstallFieldObjectHitCallbacks_020a25c4(FieldUnit *unit);
extern void UpdateFieldObjectHighlight_020a227c(FieldUnit *unit, int flag);
extern void func_ov016_020a6954(FieldUnit *unit, void (*callback)(FieldUnit *self));
extern void func_ov032_020bd518(FieldUnit *self);

void ApplyGroupMemberKind_020bc1e8(FieldUnit *unit, int kind)
{
    ActorNode *actor = func_02036240(unit->actorId);
    ActorNode *owner = func_02036240(unit->actorId);
    CollisionHost *host = func_02036230();
    UnitModel *model;

    if (host != NULL && host->world != NULL && (owner->flags & 0x10)) {
        owner->flags &= ~0x10;
        func_02033c3c(*host->world, owner->collision);
    }
    unit->kind = kind;
    unit->behaviorFlags = 0x2000001;
    SetFieldObjectWeightByKind_020a29cc(unit, kind);
    switch (kind) {
    case 2:
        func_ov001_02086434(unit, 0);
        break;
    case 0xb:
        unit->visible = 1;
        unit->savedVisible = unit->visible;
        func_ov001_02086434(unit, 0);
        unit->motion.x = 0;
        func_01ff88c4(unit->work, 0, 0x10);
        break;
    case 7:
        unit->motion = data_02053438;
        func_ov001_02086434(unit, 0);
        break;
    case 3:
        unit->moveFlags &= ~1;
        func_ov001_02086434(unit, 0);
        break;
    case 6:
        func_ov001_02086434(unit, 1);
        unit->pose = random_next_scaled_0202aa04(4);
        break;
    case 0:
        func_ov001_02086434(unit, 0);
        break;
    case 0x10:
        func_ov001_02086434(unit, 0);
        break;
    case 5:
        unit->motion.y = nextRandom12_0202aa58() % 0x1000 + 0x1000;
        unit->motion.x = 0;
        unit->moveFlags = 0x2000;
        unit->motion.z = 0x2000;
        func_ov001_02086434(unit, 0);
        break;
    }
    InstallFieldObjectHitCallbacks_020a25c4(unit);
    UpdateFieldObjectHighlight_020a227c(unit, 1);
    func_ov016_020a6954(unit, func_ov032_020bd518);
    model = unit->desc->models[kind];
    if (model != NULL) {
        actor->rotation = 0;
        actor->scale.z = 0x1000;
        actor->scale.y = actor->scale.z;
        actor->scale.x = actor->scale.y;
        model->rotation = actor->rotation;
        model->flags |= 0x20;
        model->scale = actor->scale;
    }
}




