#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *header;
    u8 counter;
    u8 pad_05[3];
} MessageContainer;

typedef struct {
    u8 pad_000[0x38];
    void *model;
} ActorSlot;

typedef struct {
    u8 pad_000[0x14];
    u16 flags;
} AttachedActor;

typedef struct {
    u8 kind;
    u8 pad_001[7];
    u32 flags;
    u8 pad_00c[0x150];
    ActorSlot slot;
    u8 pad_198[0x194];
    u8 slotId;
    u8 pad_32d[3];
    MessageContainer *container;
    AttachedActor *attached;
} StageEntry;

typedef struct {
    u8 pad_000[0x8c];
    void *model;
    u8 pad_090[0x140];
    u8 slotId;
    u8 pad_1d1[3];
    int resIndex;
    u8 pad_1d8[0x40];
    StageEntry *owner;
} ShadowActor;

typedef struct {
    u8 pad_000[0x14];
    StageEntry *entries;
    u8 pad_018[0x338];
    ShadowActor *shadow;
} StageWork;

#define FX_F32_TO_FX32(x) ((fx32)(((x) > 0) ? ((x) * 4096.0f + 0.5f) : ((x) * 4096.0f - 0.5f)))
#define RECORD_KEY(c) ((((u32)(c)->header + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((c)->counter++ & 0x1ff))

extern u8 *data_ov035_020bc4e0;
extern char sOv041_RpgPlHeHeP2_020cf9f8[];
extern char sOv041_RpgPlClClP2_020cfa08[];
extern char data_ov041_020cf760[];
extern char sOv041_Root_020cfa18[];
extern char sOv041_Sword_020cfa20[];
extern char sOv041_Bip01Head_020cfa28[];
extern void func_ov041_020c21f4(void);
extern void func_ov041_020c2324(void);
extern void func_ov041_020c23ec(void);
extern void func_ov041_020c2450(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int kind, int flags);
extern MessageContainer *GetOrOpenMessageContainer(int index);
extern u32 FindFreeSlotId(void);
extern void ActorEntry_Init(int slot, void *entry, u16 group, const u8 *attributes, const void *shape, BOOL flag20, s8 priority);
extern void ActorSlot_SetField1CCByIndex(int index, u32 value);
extern void SetRecordSlotValue(int index, u32 value);
extern void Obj_SetWord1CC(void *slot, u32 value);
extern void Obj_SetWord1C8(void *slot, u32 value);
extern void *SND_RegisterSeq(u32 key, int kind);
extern void *func_0202c4a0(u32 key, int mode);
extern void ApplyRecordTableEntry2(int index, void *record, void *block, int kind);
extern void ActivateEntrySubobject(void *entry, void *record, void *block, int kind);
extern void ActorSlot_PlaceAndLink(void *slot, int anchor, const VecFx32 *offset);
extern void ActorSlot_AttachToParent(void *child, void *parent, void *initializationData);
extern void LoadStageActorModel(StageEntry *entry);
extern int NNS_G3dGetResDictIdxByName(void *dict, const char *name);
extern void func_ov041_020c2538(StageEntry *entry);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int polygonID);
extern void SetSceneEntryAnimation(StageEntry *entry, int anim, int blend, int reset);
extern void LoadActorAnimation(StageEntry *entry);
extern void selectJointAnimationBlend(void *state, int track, void *table, int blendIndex);
extern u32 func_0202a9e4(u32 range);
extern int *func_01ffb2f8(void *state, int track, fx32 frame);

static inline void FormatAttachName(StageEntry *entry, char *name) {
    switch (*(u8 *)entry) {
    case 0x16:
        OS_SPrintf(name, sOv041_Root_020cfa18);
        break;
    case 0x12:
        OS_SPrintf(name, sOv041_Sword_020cfa20);
        break;
    case 0x17:
        OS_SPrintf(name, sOv041_Bip01Head_020cfa28);
        break;
    }
}

void SpawnStageEntryActor(int index, int kind) {
    char path[64];
    VecFx32 offset;
    char attachName[12];
    u8 attributes[4];
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    StageEntry *entry = (StageEntry *)((u8 *)work->entries + index * 0x4b4);
    ActorSlot *slot = &entry->slot;
    MessageContainer *container;
    void *record;
    void *block;
    ShadowActor *shadow;
    AttachedActor *attached;
    void *dict;
    u8 entryKind;

    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
    switch (kind) {
    case 0xfe:
    case 0xff:
        attributes[0] = 0;
        OS_SPrintf(path, sOv041_RpgPlHeHeP2_020cf9f8);
        break;
    case 0xfd:
        attributes[0] = 0;
        OS_SPrintf(path, sOv041_RpgPlClClP2_020cfa08);
        break;
    default:
        attributes[0] = 0;
        break;
    }
    if (!(entry->flags & 1) || entry->kind == 0xfd) {
        container = entry->container = NNSi_FndAllocFromDefaultHeap(sizeof(MessageContainer));
        MIi_CpuClearFast(0, container, sizeof(MessageContainer));
        container->header = Msg_OpenContainerAndReadHeader(path, 0x12, 0);
    } else {
        container = entry->container = GetOrOpenMessageContainer(kind);
    }
    entry->slotId = FindFreeSlotId();
    ActorEntry_Init(entry->slotId, slot, 0, attributes, NULL, FALSE, 0x20);
    ActorSlot_SetField1CCByIndex(entry->slotId, (u32)func_ov041_020c21f4);
    SetRecordSlotValue(entry->slotId, (u32)func_ov041_020c2324);
    record = SND_RegisterSeq(RECORD_KEY(container), 0x12);
    block = func_0202c4a0(RECORD_KEY(container), 0xf);
    ApplyRecordTableEntry2(entry->slotId, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap(block);
    ActorSlot_PlaceAndLink(slot, 0, &offset);
    LoadStageActorModel(entry);

    entryKind = entry->kind;
    if (entryKind == 0xfd) {
        work->shadow = NNSi_FndAllocFromDefaultHeap(sizeof(ShadowActor));
        shadow = work->shadow;
        MIi_CpuClearFast(0, shadow, sizeof(ShadowActor));
        shadow->owner = entry;
        dict = NULL;
        if (slot->model != NULL) {
            dict = (u8 *)slot->model + 0x40;
        }
        shadow->resIndex = dict != NULL ? NNS_G3dGetResDictIdxByName(dict, data_ov041_020cf760) : -1;
        func_ov041_020c2538(entry);
        attributes[0] = 0;
        shadow->slotId = FindFreeSlotId();
        ActorEntry_Init(shadow->slotId, shadow, 0, attributes, NULL, FALSE, 0x20);
        Obj_SetWord1CC(shadow, (u32)func_ov041_020c23ec);
        Obj_SetWord1C8(shadow, (u32)func_ov041_020c2450);
        record = SND_RegisterSeq(RECORD_KEY(container), 0x12);
        block = func_0202c4a0(RECORD_KEY(container), 0xf);
        ApplyRecordTableEntry2(shadow->slotId, record, block, 0x12);
        NNSi_FndFreeFromDefaultHeap(block);
        NNS_G3dMdlSetMdlPolygonIDAll(shadow->model, 0x3f);
        ActorSlot_PlaceAndLink(shadow, 0, &offset);
        SetSceneEntryAnimation(entry, 0, 1, 0);
        LoadActorAnimation(entry);
    } else if (entryKind == 0xfe) {
        func_ov041_020c2538(entry);
        LoadActorAnimation(entry);
        SetSceneEntryAnimation(entry, 0, 1, 0);
    } else if (entryKind == 0x16 || entryKind == 0x12 || entryKind == 0x17) {
        FormatAttachName(entry, attachName);
        attached = entry->attached = NNSi_FndAllocFromDefaultHeap(0x1d0);
        MIi_CpuClearFast(0, attached, 0x1d0);
        ActorEntry_Init(0xffff, attached, 0, attributes, NULL, FALSE, 0x20);
        record = SND_RegisterSeq(RECORD_KEY(container), 0x12);
        block = func_0202c4a0(RECORD_KEY(container), 0xf);
        ActivateEntrySubobject(attached, record, block, 0x12);
        NNSi_FndFreeFromDefaultHeap(block);
        ActorSlot_AttachToParent(attached, slot, attachName);
        if (entry->kind == 0x17) {
            attached->flags |= 8;
            selectJointAnimationBlend((u8 *)entry + 0x170, 4, (u8 *)entry + 0x248, 0);
        }
        func_ov041_020c2538(entry);
        SetSceneEntryAnimation(entry, 0, 1, 0);
    } else {
        func_ov041_020c2538(entry);
        LoadActorAnimation(entry);
        SetSceneEntryAnimation(entry, 0, 1, 0);
        func_01ffb2f8((u8 *)slot + 0x14, 0, FX_F32_TO_FX32((float)func_0202a9e4(30)));
    }
}
