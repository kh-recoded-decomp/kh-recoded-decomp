#include "nitro/types.h"
#include "nitro/fx_types.h"

#define RetainOrInitializeSharedRecord SND_RegisterSeq
#define LoadResourceBlock LoadFileAllocFromHeapTail
#define RandomBelow NextSharedRandom16Scaled
#define SetAnimationFrame SetModelAnimationFrameWithSingleWrap

/* A message container: the archive header and the index of the next record to read. */
typedef struct {
    void *header;
    u8 counter;
    u8 pad_05[3];
} MessageContainer;

/* The actor object every stage actor starts with. */
typedef struct {
    u8 pad_000[0x14];
    u8 animState[0x24];
    void *modelResource;
    u8 pad_03c[0x50];
    void *model;
    u8 pad_090[0x5c];
    u8 animTable[0xe4];
    u8 slotId;
    u8 pad_1d1[3];
} ActorObject;

typedef struct {
    u8 kind;
    u8 pad_001[7];
    u32 flags;
    u8 pad_00c[0x150];
    ActorObject actor;
    MessageContainer *container;
} StageEntry;

/* An actor that follows a stage entry: the player's weapon and the player's shadow. */
typedef struct {
    ActorObject actor;
    int nodeIndex;
    u8 pad_1d8[0x34];
    MessageContainer container;
    u32 soundArc;
    StageEntry *owner;
} FollowerActor;

typedef struct {
    u8 pad_000[0x14];
    StageEntry *entries;
    u8 pad_018[0xe0];
    FollowerActor weapon;
    u8 pad_314[0x38];
    FollowerActor *shadow;
} StageWork;

typedef struct {
    u8 pad_00[0x10];
    u8 colorIndex;
    u8 pad_11[0xb];
    s16 soundIndex;
} OverlaySelectionRecord;

#define FX_F32_TO_FX32(x) ((fx32)(((x) > 0) ? ((x) * 4096.0f + 0.5f) : ((x) * 4096.0f - 0.5f)))
#define RECORD_KEY(header, counter) ((((u32)(header) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((counter)++ & 0x1ff))

extern u8 *gMovieContextState;
extern char sOv041_RpgPlSoSoP2_020cfa34[];
extern char sOv041_WeaponTg00_020cf770[];
extern char sOv041_RpgPlSoWeP2_020cfa44[];
extern const char data_ov041_020cf790[];
extern void UpdateStageEntryAnimation(void);
extern void DrawStageEntryModels(void);
extern void DrawStagePrimaryModel(void);
extern void UpdateStageShadowActor(void);
extern void DrawTrackedStageShadow(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int kind, int flags);
extern u32 FindFreeSlotId(void);
extern void ActorEntry_Init(int slot, void *entry, u16 group, const u8 *attributes, const void *shape, BOOL flag20,
                            s8 priority);
extern void ActorSlot_SetField1CCByIndex(int index, u32 value);
extern void SetRecordSlotValue(int index, u32 value);
extern void Obj_SetWord1CC(void *slot, u32 value);
extern void Obj_SetWord1C8(void *slot, u32 value);
extern void *RetainOrInitializeSharedRecord(u32 key, int kind);
extern void *LoadResourceBlock(u32 key, int kind);
extern BOOL ApplyRecordTableEntry2(int index, void *record, void *block, int kind);
extern void ActorSlot_PlaceAndLink(void *slot, int anchor, const VecFx32 *offset);
extern void selectJointAnimationBlend(void *state, int track, void *table, int blendIndex);
extern u32 RandomBelow(u32 range);
extern int *SetAnimationFrame(void *state, int track, fx32 frame);
extern void LoadStageActorModel(StageEntry *entry);
extern void InstallModelRenderCallback(StageEntry *entry);
extern int NNS_G3dGetResDictIdxByName(void *dict, const char *name);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 index);
extern BOOL InitSharedRecordThenTexture(void *dst, void *src, u32 key, int flags);
extern void QueueSoundCommandForArc(u32 archive);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int polygonID);
extern void LoadActorAnimation(StageEntry *entry);

/*
 * Builds the player's stage entry (slot 0xff): Sora's model and animations from
 * rpg/pl/so/so.p2, the weapon attached to his "weapon_tg00" node from
 * rpg/pl/so/we.p2 in the selected colour, and the shadow that tracks his "Root"
 * node. The original compiled this function at optimisation level 2 with the
 * 1.1p1 compiler: level 2 keeps the actor pointer, reused for the weapon, in one
 * spill slot, and that compiler reloads the record counter after each constant
 * store where 1.1 reuses the constant.
 */
#pragma push
#pragma optimization_level 2
void SpawnPlayerStageEntryActor(int index, u8 slot)
{
    char path[64];
    VecFx32 offset;
    u8 attributes[4];
    StageWork *work = *(StageWork **)(gMovieContextState + 0xb8);
    StageEntry *entry = (StageEntry *)((u8 *)work->entries + index * 0x4b4);
    ActorObject *actor = &entry->actor;
    MessageContainer *container;
    void *record;
    void *block;
    FollowerActor *shadow;
    void *weaponDict;
    void *shadowDict;

    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
    if (slot == 0xff) {
        entry->flags &= ~1;
        attributes[0] = 0;
        OS_SPrintf(path, sOv041_RpgPlSoSoP2_020cfa34);
    }
    container = entry->container = NNSi_FndAllocFromDefaultHeap(sizeof(MessageContainer));
    MIi_CpuClearFast(0, container, sizeof(MessageContainer));
    container->header = Msg_OpenContainerAndReadHeader(path, 0x12, 0);
    entry->actor.slotId = FindFreeSlotId();
    ActorEntry_Init(entry->actor.slotId, actor, 0, attributes, NULL, FALSE, 0x20);
    ActorSlot_SetField1CCByIndex(entry->actor.slotId, (u32)UpdateStageEntryAnimation);
    SetRecordSlotValue(entry->actor.slotId, (u32)DrawStageEntryModels);
    record = RetainOrInitializeSharedRecord(RECORD_KEY(container->header, container->counter), 0x12);
    block = LoadResourceBlock(RECORD_KEY(container->header, container->counter), 0xf);
    ApplyRecordTableEntry2(entry->actor.slotId, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap(block);
    ActorSlot_PlaceAndLink(actor, 0, &offset);
    selectJointAnimationBlend(entry->actor.animState, 0, actor->animTable, 0);
    SetAnimationFrame(actor->animState, 0, FX_F32_TO_FX32((float)RandomBelow(30)));
    LoadStageActorModel(entry);
    InstallModelRenderCallback(entry);

    /* The weapon follows the player's "weapon_tg00" node. */
    work->weapon.owner = entry;
    weaponDict = NULL;
    if (actor->modelResource != NULL) {
        weaponDict = (u8 *)actor->modelResource + 0x40;
    }
    work->weapon.nodeIndex =
        weaponDict != NULL ? NNS_G3dGetResDictIdxByName(weaponDict, sOv041_WeaponTg00_020cf770) : -1;
    actor = &work->weapon.actor;
    shadowDict = NULL;
    attributes[0] = 0;
    work->weapon.actor.slotId = FindFreeSlotId();
    ActorEntry_Init(work->weapon.actor.slotId, actor, 0, attributes, NULL, FALSE, 0x20);
    Obj_SetWord1C8(actor, (u32)DrawStagePrimaryModel);
    container = &work->weapon.container;
    work->weapon.container.header = Msg_OpenContainerAndReadHeader(sOv041_RpgPlSoWeP2_020cfa44, 0x12, 0);
    container->counter = GetOverlaySelectionRecord(0)->colorIndex * 2;
    record = RetainOrInitializeSharedRecord(RECORD_KEY(work->weapon.container.header, container->counter), 0x12);
    block = LoadResourceBlock(RECORD_KEY(work->weapon.container.header, container->counter), 0xf);
    ApplyRecordTableEntry2(work->weapon.actor.slotId, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap(block);
    ActorSlot_PlaceAndLink(actor, 0, &offset);
    container->counter = 0x16;
    InitSharedRecordThenTexture(actor->animTable, actor->animState,
                                RECORD_KEY(work->weapon.container.header, container->counter), 0x12);
    selectJointAnimationBlend(actor->animState, 0, actor->animTable, 0);
    work->weapon.soundArc = GetOverlaySelectionRecord(0)->soundIndex + 0x48;
    QueueSoundCommandForArc(work->weapon.soundArc);

    /* The shadow follows the player's "Root" node and reads its records from the weapon archive. */
    work->shadow = NNSi_FndAllocFromDefaultHeap(sizeof(FollowerActor));
    shadow = work->shadow;
    MIi_CpuClearFast(0, shadow, sizeof(FollowerActor));
    shadow->owner = entry;
    if (entry->actor.modelResource != NULL) {
        shadowDict = (u8 *)entry->actor.modelResource + 0x40;
    }
    shadow->nodeIndex = shadowDict != NULL ? NNS_G3dGetResDictIdxByName(shadowDict, data_ov041_020cf790) : -1;
    attributes[0] = 0;
    shadow->actor.slotId = FindFreeSlotId();
    ActorEntry_Init(shadow->actor.slotId, shadow, 0, attributes, NULL, FALSE, 0x20);
    Obj_SetWord1CC(shadow, (u32)UpdateStageShadowActor);
    Obj_SetWord1C8(shadow, (u32)DrawTrackedStageShadow);
    container->counter += (u8)(GetOverlaySelectionRecord(0)->colorIndex * 2);
    record = RetainOrInitializeSharedRecord(RECORD_KEY(container->header, container->counter), 0x12);
    block = LoadResourceBlock(RECORD_KEY(container->header, container->counter), 0xf);
    ApplyRecordTableEntry2(shadow->actor.slotId, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap(block);
    container->counter = 0x2d;
    InitSharedRecordThenTexture(shadow->actor.animTable, shadow->actor.animState,
                                RECORD_KEY(container->header, container->counter), 0x12);
    selectJointAnimationBlend(shadow->actor.animState, 0, shadow->actor.animTable, 0);
    NNS_G3dMdlSetMdlPolygonIDAll(shadow->actor.model, 0x3f);
    ActorSlot_PlaceAndLink(shadow, 0, &offset);
    LoadActorAnimation(entry);
}
#pragma pop
