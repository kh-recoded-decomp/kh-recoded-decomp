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
extern char data_ov041_020cf9d8[];
extern char data_ov041_020cf9e8[];
extern char data_ov041_020cf740[];
extern char data_ov041_020cf9f8[];
extern char data_ov041_020cfa00[];
extern char data_ov041_020cfa08[];
extern void func_ov041_020c21d5(void);
extern void func_ov041_020c2305(void);
extern void func_ov041_020c23cd(void);
extern void func_ov041_020c2431(void);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int kind, int flags);
extern MessageContainer *GetOrOpenMessageContainer_020bd62c(int index);
extern u32 FindFreeSlotId_020c21b0(void);
extern void ActorEntry_Init_020357d8(int slot, void *entry, u16 group, const u8 *attributes, const void *shape, BOOL flag20, s8 priority);
extern void ActorSlot_SetField1CCByIndex_02036a98(int index, u32 value);
extern void func_02036a70(int index, u32 value);
extern void func_02036ab8(void *slot, u32 value);
extern void func_02036a90(void *slot, u32 value);
extern void *RetainOrInitializeSharedRecord_0202c80c(u32 key, int kind);
extern void *func_0202c48c(u32 key, int mode);
extern void func_020358b0(int index, void *record, void *block, int kind);
extern void func_02035930(void *entry, void *record, void *block, int kind);
extern void ActorSlot_PlaceAndLink_02035a18(void *slot, int anchor, const VecFx32 *offset);
extern void ActorSlot_AttachToParent_02035b74(void *child, void *parent, void *initializationData);
extern void LoadStageActorModel_020c26b8(StageEntry *entry);
extern int FindResourceIndexByName_0201aafc(void *dict, const char *name);
extern void InstallModelRenderCallback_020c2518(StageEntry *entry);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonID);
extern void SetSceneEntryAnimation_020c278c(StageEntry *entry, int anim, int blend, int reset);
extern void LoadActorAnimation_020c36ec(StageEntry *entry);
extern void selectJointAnimationBlend_0202f2cc(void *state, int track, void *table, int blendIndex);
extern u32 func_0202a9d0(u32 range);
extern int *func_01ffb2f8(void *state, int track, fx32 frame);

static inline void FormatAttachName(StageEntry *entry, char *name) {
    switch (*(u8 *)entry) {
    case 0x16:
        OS_SPrintf_02002428(name, data_ov041_020cf9f8);
        break;
    case 0x12:
        OS_SPrintf_02002428(name, data_ov041_020cfa00);
        break;
    case 0x17:
        OS_SPrintf_02002428(name, data_ov041_020cfa08);
        break;
    }
}

void SpawnStageEntryActor_020c18cc(int index, int kind) {
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
        OS_SPrintf_02002428(path, data_ov041_020cf9d8);
        break;
    case 0xfd:
        attributes[0] = 0;
        OS_SPrintf_02002428(path, data_ov041_020cf9e8);
        break;
    default:
        attributes[0] = 0;
        break;
    }
    if (!(entry->flags & 1) || entry->kind == 0xfd) {
        container = entry->container = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(MessageContainer));
        func_01ff8740(0, container, sizeof(MessageContainer));
        container->header = Msg_OpenContainerAndReadHeader_0202cc6c(path, 0x12, 0);
    } else {
        container = entry->container = GetOrOpenMessageContainer_020bd62c(kind);
    }
    entry->slotId = FindFreeSlotId_020c21b0();
    ActorEntry_Init_020357d8(entry->slotId, slot, 0, attributes, NULL, FALSE, 0x20);
    ActorSlot_SetField1CCByIndex_02036a98(entry->slotId, (u32)func_ov041_020c21d5);
    func_02036a70(entry->slotId, (u32)func_ov041_020c2305);
    record = RetainOrInitializeSharedRecord_0202c80c(RECORD_KEY(container), 0x12);
    block = func_0202c48c(RECORD_KEY(container), 0xf);
    func_020358b0(entry->slotId, record, block, 0x12);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    ActorSlot_PlaceAndLink_02035a18(slot, 0, &offset);
    LoadStageActorModel_020c26b8(entry);

    entryKind = entry->kind;
    if (entryKind == 0xfd) {
        work->shadow = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(ShadowActor));
        shadow = work->shadow;
        func_01ff8740(0, shadow, sizeof(ShadowActor));
        shadow->owner = entry;
        dict = NULL;
        if (slot->model != NULL) {
            dict = (u8 *)slot->model + 0x40;
        }
        shadow->resIndex = dict != NULL ? FindResourceIndexByName_0201aafc(dict, data_ov041_020cf740) : -1;
        InstallModelRenderCallback_020c2518(entry);
        attributes[0] = 0;
        shadow->slotId = FindFreeSlotId_020c21b0();
        ActorEntry_Init_020357d8(shadow->slotId, shadow, 0, attributes, NULL, FALSE, 0x20);
        func_02036ab8(shadow, (u32)func_ov041_020c23cd);
        func_02036a90(shadow, (u32)func_ov041_020c2431);
        record = RetainOrInitializeSharedRecord_0202c80c(RECORD_KEY(container), 0x12);
        block = func_0202c48c(RECORD_KEY(container), 0xf);
        func_020358b0(shadow->slotId, record, block, 0x12);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
        Model_SetAllPolygonIds_0201a8c0(shadow->model, 0x3f);
        ActorSlot_PlaceAndLink_02035a18(shadow, 0, &offset);
        SetSceneEntryAnimation_020c278c(entry, 0, 1, 0);
        LoadActorAnimation_020c36ec(entry);
    } else if (entryKind == 0xfe) {
        InstallModelRenderCallback_020c2518(entry);
        LoadActorAnimation_020c36ec(entry);
        SetSceneEntryAnimation_020c278c(entry, 0, 1, 0);
    } else if (entryKind == 0x16 || entryKind == 0x12 || entryKind == 0x17) {
        FormatAttachName(entry, attachName);
        attached = entry->attached = NNSi_FndAllocFromDefaultHeap_0202a178(0x1d0);
        func_01ff8740(0, attached, 0x1d0);
        ActorEntry_Init_020357d8(0xffff, attached, 0, attributes, NULL, FALSE, 0x20);
        record = RetainOrInitializeSharedRecord_0202c80c(RECORD_KEY(container), 0x12);
        block = func_0202c48c(RECORD_KEY(container), 0xf);
        func_02035930(attached, record, block, 0x12);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
        ActorSlot_AttachToParent_02035b74(attached, slot, attachName);
        if (entry->kind == 0x17) {
            attached->flags |= 8;
            selectJointAnimationBlend_0202f2cc((u8 *)entry + 0x170, 4, (u8 *)entry + 0x248, 0);
        }
        InstallModelRenderCallback_020c2518(entry);
        SetSceneEntryAnimation_020c278c(entry, 0, 1, 0);
    } else {
        InstallModelRenderCallback_020c2518(entry);
        LoadActorAnimation_020c36ec(entry);
        SetSceneEntryAnimation_020c278c(entry, 0, 1, 0);
        func_01ffb2f8((u8 *)slot + 0x14, 0, FX_F32_TO_FX32((float)func_0202a9d0(30)));
    }
}
