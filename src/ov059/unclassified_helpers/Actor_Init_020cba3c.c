#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorFunc)(Actor *actor);
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);
typedef void (*ActorActionEndFunc)(Actor *actor, int result, int arg);

typedef struct QueryCallback {
    void *func;
    void *arg;
} QueryCallback;

typedef struct EntryGroupDesc {
    int resourceId;
    u32 animationId;
    s32 slotCount;
    u32 modelId;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct EntryGroupTemplate {
    u32 fileId;
    s32 slotCount;
    s16 *groupId;
} EntryGroupTemplate;

typedef struct EntryGroupTable {
    EntryGroupTemplate entries[5];
} EntryGroupTable;

struct Actor {
    u8 pad_0000[0x1f8];
    ActorActionEndFunc onActionEnd;
    u8 pad_01fc[0x6ac - 0x1fc];
    VecFx32 motionOffset;
    u8 pad_06b8[0x930 - 0x6b8];
    u8 playerIndex;
    u8 flag931;
    u8 pad_0932[2];
    u32 state934 : 8;
    u32 rest934 : 24;
    u8 state938 : 8;
    u8 pad_0939[3];
    s32 cueGroup;
    u8 pad_0940[4];
    s32 mode;
    u8 pad_0948[4];
    VecFx32 guardPoint;
    u8 pad_0958[4];
    s32 guardTimer;
    u8 pad_0960[0x970 - 0x960];
    u8 motionTarget[0x998 - 0x970];
    u8 cueTable[0x9d4 - 0x998];
    u8 trackers[2][0x230];
    u8 record68[0xec4 - 0xe34];
    u8 effects[0x1524 - 0xec4];
    u8 sprites[0x16f0 - 0x1524];
    u8 blendSets[0x1708 - 0x16f0];
    s32 pendingCommand;
    s32 commandKinds[1];
    u8 commandReady;
    s8 commandIndex;
    u8 pad_1712[0x171c - 0x1712];
    u32 chargePhase : 8;
    u32 chargeLevel : 6;
    u32 effectActive : 1;
    u32 chargeFlags : 17;
    u8 pad_1720[0x1728 - 0x1720];
    s32 field_1728;
    s32 chargeTimer;
    s32 field_1730;
    s32 field_1734;
    u8 pad_1738[0x1744 - 0x1738];
    void *chargeBuffer;
    u8 pad_1748[0x1774 - 0x1748];
    u8 quadNode[0x17e4 - 0x1774];
    QueryCallback filter;
    QueryCallback callback;
    u8 pad_17f4[0x17fc - 0x17f4];
    u32 chargeSound;
    u8 pad_1800[4];
    ActorFunc onInit;
    ActorChangeStateFunc changeState;
    u8 pad_180c[0x1812 - 0x180c];
    s16 groupIds[6];
    u8 pad_181e[0x1820 - 0x181e];
    s32 guardStock;
    s32 heapGroup;
};

extern Actor *data_ov059_020cffa4;
extern const char data_ov059_020cff64[];
extern const EntryGroupTable data_ov059_020cfe7c;

extern void func_ov059_020c7acc(Actor *actor);
extern s32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void Actor_SetTimeScale_020c7d88(Actor *actor, fx32 scale);
extern void func_ov059_020c932c(void *target);
extern void ClearRecord68_020aa1dc(void *record);
extern void InitSlotTable_020a98e8(void *obj, u8 kind);
extern void EffectGroup_Init_020cedbc(Actor *owner, void *group);
extern void func_ov059_020cf8d8(void *sprites);
extern void func_01ff86fc(u32 data, void *dest, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern BOOL InitCollisionObject_02033c7c(void *object, u16 groupMask, s32 ownerId);
extern BOOL QueryFilter_IsKind24_020ca1d4(void);
extern void func_ov059_020ca1e8(void);
extern void func_ov021_020a7cc8(void *table, s32 group, u8 playerIndex);
extern void ZeroBytes0x14_020a8adc(void *obj);
extern int func_ov021_020a89a8(EntryGroupDesc *desc);
extern void Actor_LoadJointBlendSets_020c8a84(Actor *actor, void *blendSets);
extern void RegisterSessionCallback_0206c704(void (*callback)(void));
extern void func_ov059_020cbe80(void);

void Actor_Init_020cba3c(Actor *actor)
{
    EntryGroupDesc desc;
    EntryGroupTable groups;
    QueryCallback filter;
    QueryCallback callback;
    int i;
    u32 j;

    data_ov059_020cffa4 = actor;
    func_ov059_020c7acc(actor);
    actor->heapGroup = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov059_020cff64, 8, FALSE);
    actor->guardPoint.z = 0;
    actor->guardPoint.y = 0;
    actor->guardPoint.x = 0;
    actor->motionOffset.z = 0;
    actor->motionOffset.y = 0;
    actor->motionOffset.x = 0;
    Actor_SetTimeScale_020c7d88(actor, 0x1000);
    actor->mode = 0;
    actor->guardTimer = 0;
    actor->guardStock = -1;
    func_ov059_020c932c(actor->motionTarget);
    ClearRecord68_020aa1dc(actor->record68);
    for (i = 0; i < 2; i++) {
        InitSlotTable_020a98e8(actor->trackers[i], actor->playerIndex);
    }
    EffectGroup_Init_020cedbc(actor, actor->effects);
    func_ov059_020cf8d8(actor->sprites);
    actor->flag931 = 0;
    actor->state934 = 0;
    actor->state938 = 0;
    actor->commandReady = 0;
    actor->commandIndex = -1;
    func_01ff86fc(0, actor->commandKinds, sizeof(actor->commandKinds));
    actor->field_1728 = 0;
    actor->pendingCommand = -1;
    actor->chargePhase = 1;
    actor->chargeLevel = 0;
    actor->chargeTimer = 0x7fffffff;
    actor->chargeBuffer = NNSi_FndAllocFromDefaultHeap_0202a178(0x38);
    actor->effectActive = 0;
    InitCollisionObject_02033c7c(actor->quadNode, 0, 0);
    filter.func = QueryFilter_IsKind24_020ca1d4;
    filter.arg = actor;
    actor->filter = filter;
    callback.func = func_ov059_020ca1e8;
    callback.arg = actor;
    actor->callback = callback;
    actor->chargeSound = 0;
    actor->field_1730 = 0;
    actor->field_1734 = -1;
    actor->commandReady = 1;
    actor->commandKinds[0] = 0;
    actor->commandIndex = 0;
    func_ov021_020a7cc8(actor->cueTable, actor->cueGroup, actor->playerIndex);
    ZeroBytes0x14_020a8adc(&desc);
    desc.animationId = 1;
    desc.modelId = 0;
    groups = data_ov059_020cfe7c;
    groups.entries[0].groupId = &actor->groupIds[0];
    groups.entries[1].groupId = &actor->groupIds[1];
    groups.entries[2].groupId = &actor->groupIds[2];
    groups.entries[3].groupId = &actor->groupIds[4];
    groups.entries[4].groupId = &actor->groupIds[5];
    for (j = 0; j < 5; j++) {
        EntryGroupTemplate *group = &groups.entries[j];
        u32 fileId = group->fileId;
        u32 high = (((actor->heapGroup + 0x8000) & 0xfffffc) << 7) | 0x80000000;

        desc.modelId = (fileId & 0x1ff) | high;
        desc.animationId = high | ((fileId + 1) & 0x1ff);
        desc.slotCount = group->slotCount;
        *group->groupId = func_ov021_020a89a8(&desc);
    }
    Actor_LoadJointBlendSets_020c8a84(actor, actor->blendSets);
    if (actor->onInit != NULL) {
        actor->onInit(actor);
    }
    actor->changeState(actor, 1);
    if (actor->onActionEnd != NULL) {
        actor->onActionEnd(actor, 1, -1);
    }
    RegisterSessionCallback_0206c704(func_ov059_020cbe80);
}
