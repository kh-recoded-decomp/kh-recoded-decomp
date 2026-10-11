#include "nitro/types.h"

typedef struct ActorDef ActorDef;

typedef struct StageActor {
    u8 pad_000[0x8];
    u16 flags;
    u8 pad_00a[0x2];
    u8 kind;
    u8 slot;
    u8 state;
    u8 pad_00f[0x1b9];
    int paramB;
    int paramA;
    u16 defId;
    u16 ownerId;
    u8 pad_1d4[0x98];
    u32 mask : 31;
    u32 maskTop : 1;
    u16 variant;
    u8 pad_272[0x6];
    ActorDef *def;
    u16 mode;
    u16 group;
    u8 pad_280[0x148];
} StageActor;

struct ActorDef {
    int id;
    int kind;
    int flags;
    u32 mask;
    void (*init)(StageActor *actor);
    int pad_14;
    int paramA;
    int paramB;
};

typedef struct SpawnInfo {
    u16 defId;
    u16 ownerId;
    u16 variant;
} SpawnInfo;

extern ActorDef data_ov001_020a0240;
extern u16 ReleaseStageSlot_0209c008(int index);
extern StageActor *GetStageActor_0209c040(int id);
extern void func_01ff8830(void *dst, int value, int size);
extern void func_ov001_02090d98(StageActor *actor, int group, int mode, int extra, SpawnInfo *info);

int CreateStageActor_02091834(ActorDef *def, u16 ownerId, u16 variant, u16 group, u16 mode, int extra)
{
    u16 slot;
    StageActor *actor;
    SpawnInfo info;


    slot = ReleaseStageSlot_0209c008(3);
    if (slot == 0) {
        return 0;
    }
    actor = GetStageActor_0209c040((s16)slot);
    func_01ff8830(actor, 0, sizeof(StageActor));
    if (mode == 0) {
        mode = 0xffff;
    }
    if (def == NULL) {
        def = &data_ov001_020a0240;
    }
    if (ownerId == 0) {
        ownerId = slot;
    }
    actor->defId = def->id;
    actor->ownerId = ownerId;
    actor->variant = variant;
    info.defId = def->id;
    info.ownerId = ownerId;
    info.variant = variant;
    if (def->init != NULL) {
        def->init(actor);
    }
    func_ov001_02090d98(actor, group, mode, extra, &info);
    actor->group = group;
    actor->mode = mode;
    actor->def = def;
    actor->paramA = def->paramA;
    actor->paramB = def->paramB;
    actor->slot = slot;
    actor->state = 0;
    actor->kind = def->kind;
    actor->mask |= def->mask;
    actor->flags |= def->flags;
    return slot;
}
