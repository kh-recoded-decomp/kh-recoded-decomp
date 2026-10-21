#pragma inline_max_size(10000)
#include "nitro/types.h"

typedef struct FileSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} FileSection;

typedef struct StageFile {
    u8 pad_00[8];
    FileSection *sections;
} StageFile;

typedef struct StageEntry {
    u16 id;
    u8 pad_02[2];
    StageFile *file;
} StageEntry;

typedef struct SpawnSetup {
    u32 linkTarget;
    u32 trigger;
    u8 solid;
    u8 pad_09;
    u8 heavy;
    u8 pad_0b[0x18 - 0xb];
    u8 kind;
} SpawnSetup;

typedef struct SpawnParams {
    u8 pad_00[0x14];
    u8 mirrored;
    u8 layer;
    u8 hidden;
} SpawnParams;

typedef struct ObjectGroup {
    u8 pad_00[4];
    u16 resourceBase;
    u8 pad_06[0xe - 6];
    u16 shapeBase;
    u8 pad_10[0x1a - 0x10];
    u16 linkBase;
} ObjectGroup;

typedef struct ShapeEntry {
    u8 pad_00[4];
    u32 nameIndex;
    u8 pad_08[4];
    u32 radius;
} ShapeEntry;

typedef struct ResourceEntry {
    u32 nameIndex;
    u8 isDefault;
    u8 visible;
} ResourceEntry;

typedef struct ColliderList {
    u8 pad_00[4];
    u32 count;
} ColliderList;

typedef struct ShapeParams {
    u8 pad_00[4];
    u32 size;
    u8 pad_08[0x14 - 8];
} ShapeParams;

typedef struct SmallRecord {
    u8 unk_00;
    u8 kind;
} SmallRecord;

typedef struct StageObjectRecord {
    u8 pad_000[0x114];
    u16 variant;
} StageObjectRecord;

typedef struct SpawnPair {
    u32 first;
    u32 second;
} SpawnPair;

typedef struct StageActor {
    u8 pad_000[8];
    u16 drawFlags;
    u8 pad_00a[0x184 - 0xa];
    SpawnPair anim;
    u8 pad_18c[0x1c0 - 0x18c];
    u32 linkTarget;
    u8 pad_1c4[0x26c - 0x1c4];
    u32 behaviorFlags : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x27e - 0x270];
    u16 recordId;
    u8 pad_280[0x288 - 0x280];
    u16 layer : 2;
    u16 visibility : 2;
    u16 unk_288_4 : 5;
    u16 mirrored : 1;
    u16 unk_288_10 : 5;
    u16 heavy : 1;
    u16 unk_28a_0 : 14;
    u16 hidden : 1;
    u16 noFloor : 1;
    u16 variant : 3;
    u16 unk_28c_3 : 13;
    u8 pad_28e[0x294 - 0x28e];
    u32 unk_294;
    u32 spawnB;
    u8 pad_29c[0x2b0 - 0x29c];
    u32 trigger;
    u32 radius;
    u8 pad_2b8[0x2bc - 0x2b8];
    u32 shapeSize;
    u8 pad_2c0[0x2e5 - 0x2c0];
    u8 alpha;
    u8 pad_2e6[0x398 - 0x2e6];
    s32 mass;
    u8 pad_39c[0x3a4 - 0x39c];
    u16 unk_3a4;
    u8 pad_3a6[2];
    u16 unk_3a8;
    u8 pad_3aa[0x3c4 - 0x3aa];
    void *message;
} StageActor;

typedef struct SpawnRecord {
    u8 pad_00[0xa];
    u8 hidden;
    u8 pad_0b[0xe - 0xb];
    u16 slot;
    u16 actorId;
    u8 pad_12[0x1a - 0x12];
    u16 tableIndex;
    u8 pad_1c[0x48 - 0x1c];
    s32 mass;
    u32 spawnB;
    u8 pad_50[0x61 - 0x50];
    u8 noFloor;
    u8 static_;
} SpawnRecord;

typedef struct ActorDesc ActorDesc;

extern ActorDesc data_ov001_020a02a8;
extern const char data_ov001_020a02e4[];

extern SmallRecord *GetSmallTableEntry_0209c340(int index);
extern ShapeParams *GetCollisionShapeParams_02093114(ShapeEntry *source, ShapeParams *params);
extern u16 FindStageObjectByOwner_020995c4(u16 slot, u32 owner);
extern u16 GetStageRowIndex_0209c228(int offset);
extern int func_ov001_02091834(ActorDesc *desc, int row, u16 kind, u32 object, u16 owner, ShapeParams *shape);
extern StageActor *GetStageActor_0209c040(int id);
extern StageObjectRecord *GetStageObjectRecord_0209c0a0(u32 id);
extern void *OS_SNPrintf_02002468(char *dst, unsigned int len, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern s32 func_ov001_0208f018(u8 *ctx, int index);
extern void AttachActorResource_020914b8(StageActor *actor, const char *name, int isDefault, int visible);
extern void AttachActorCollider_020912a8(StageActor *owner, ShapeEntry *params, const char *name);
extern void SetLinkedActorsInQuadTree_020917d8(void *actor, BOOL insert);

static inline u32 GetEntrySectionCount(StageEntry *entry, int type)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->file == NULL) {
        return 0;
    }
    if (type < 0) {
        return 0;
    }
    if (type >= 0x13) {
        return 0;
    }
    return entry->file->sections[type].count;
}

static inline u8 *GetEntrySectionItem(StageEntry *entry, int type, u32 index)
{
    u32 count;
    FileSection *sections;
    u8 *data;

    if (entry == NULL) {
        return NULL;
    }
    if (entry->file == NULL) {
        return NULL;
    }
    if (type < 0) {
        return NULL;
    }
    if (type >= 0x13) {
        return NULL;
    }
    count = GetEntrySectionCount(entry, type);
    sections = entry->file->sections;
    data = sections[type].data;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return data + index * sections[type].stride;
}

static inline ObjectGroup *GetObjectGroup(StageEntry *entry, u16 index)
{
    return (ObjectGroup *)GetEntrySectionItem(entry, 0x11, index);
}

static inline ShapeEntry *GetShapeEntry(StageEntry *entry, u16 index)
{
    return (ShapeEntry *)GetEntrySectionItem(entry, 7, index);
}

static inline ColliderList *GetColliderList(StageEntry *entry, u16 index)
{
    return (ColliderList *)GetEntrySectionItem(entry, 0xd, index);
}

static inline ShapeEntry *GetGroupShape(StageEntry *entry, u16 index, u16 sub)
{
    u16 base = 0;

    if (index != 0) {
        ObjectGroup *group = GetObjectGroup(entry, index - 1);
        if (group == NULL) {
            return NULL;
        }
        base = group->shapeBase;
    }
    return GetShapeEntry(entry, base + sub);
}

static inline ResourceEntry *FinishResourceLookup(StageEntry *entry, u32 count, u32 index)
{
    FileSection *sections = entry->file->sections;
    u8 *data = sections[2].data;

    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (ResourceEntry *)(data + index * sections[2].stride);
}

static inline ResourceEntry *GetGroupResource(StageEntry *entry, u16 index, u16 sub)
{
    u16 base = 0;
    u32 count;

    if (index != 0) {
        ObjectGroup *group = GetObjectGroup(entry, index - 1);
        if (group == NULL) {
            return NULL;
        }
        base = group->resourceBase;
    }
    if (entry == NULL) {
        return NULL;
    }
    if (entry->file == NULL) {
        return NULL;
    }
    if (entry == NULL) {
        count = 0;
    } else if (entry->file == NULL) {
        count = 0;
    } else {
        count = entry->file->sections[2].count;
    }
    return FinishResourceLookup(entry, count, (u16)(base + sub));
}

static inline ColliderList *GetGroupColliders(StageEntry *entry, u16 index, u16 sub)
{
    u16 base = 0;

    if (index != 0) {
        ObjectGroup *group = GetObjectGroup(entry, index - 1);
        if (group == NULL) {
            return NULL;
        }
        base = group->linkBase;
    }
    return GetColliderList(entry, base + sub);
}

static inline SpawnParams *GetSpawnParamsEntry(StageEntry *entry, u16 index)
{
    return (SpawnParams *)GetEntrySectionItem(entry, 4, index);
}

static inline SpawnParams *GetSpawnParams(StageEntry *entry, u16 index)
{
    u16 slot = index;

    return GetSpawnParamsEntry(entry, slot);
}

static inline ShapeEntry *FinishShapeLookup(StageEntry *entry, u32 count, u32 index)
{
    FileSection *sections = entry->file->sections;
    u8 *data = sections[7].data;

    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (ShapeEntry *)(data + index * sections[7].stride);
}

static inline ShapeEntry *GetGroupCollider(StageEntry *entry, u16 index, u16 sub)
{
    u16 base = 0;
    u32 count;

    if (index != 0) {
        ObjectGroup *group = GetObjectGroup(entry, index - 1);
        if (group == NULL) {
            return NULL;
        }
        base = group->shapeBase;
    }
    if (entry == NULL) {
        return NULL;
    }
    if (entry->file == NULL) {
        return NULL;
    }
    if (entry == NULL) {
        count = 0;
    } else if (entry->file == NULL) {
        count = 0;
    } else {
        count = entry->file->sections[7].count;
    }
    return FinishShapeLookup(entry, count, (u16)(base + sub));
}

static inline int GetGroupResourceCount(StageEntry *entry, u16 index)
{
    ObjectGroup *prev;
    ObjectGroup *cur;

    if (index == 0) {
        cur = GetObjectGroup(entry, index);
        if (cur != NULL) {
            return cur->resourceBase;
        }
    } else {
        prev = GetObjectGroup(entry, index - 1);
        cur = GetObjectGroup(entry, index);
        if (prev != NULL && cur != NULL) {
            return cur->resourceBase - prev->resourceBase;
        }
    }
    return 0;
}

static inline SpawnPair MakeSpawnPair(u32 first, u32 second)
{
    SpawnPair pair;

    pair.first = first;
    pair.second = second;
    return pair;
}

int SpawnStageGroupActor_020950f8(SpawnRecord *record, StageEntry *entry, u16 index, u16 owner)
{
    ShapeParams shapeBuf;
    char path[0x40];
    SpawnSetup *setup;
    ShapeParams *shapeParams;
    ShapeEntry *shape;
    SpawnParams *params;
    ColliderList *colliders;
    StageActor *actor;
    ResourceEntry *resource;
    ShapeEntry *collider;
    StageObjectRecord *objectRecord;
    u16 object;
    u16 count;
    u16 i;
    BOOL visible;
    int actorId;
    u8 kind;

    kind = 0;
    if (record->tableIndex != 0xffff) {
        SmallRecord *small = GetSmallTableEntry_0209c340(record->tableIndex);
        if (small != NULL) {
            kind = small->kind;
        }
    }
    if (entry == NULL) {
        return 0;
    }
    setup = (SpawnSetup *)GetEntrySectionItem(entry, 0, 0);
    if (setup == NULL) {
        return 0;
    }
    shape = GetGroupShape(entry, index, 0);
    params = GetSpawnParams(entry, index);
    if (params == NULL) {
        return 0;
    }
    shapeParams = GetCollisionShapeParams_02093114(shape, &shapeBuf);
    object = FindStageObjectByOwner_020995c4((u16)(index + record->slot * 100), 0);
    if (object == 0) {
        return 0;
    }
    if (index == 0) {
        actorId = func_ov001_02091834(&data_ov001_020a02a8, GetStageRowIndex_0209c228((int)record), kind, object, owner, shapeParams);
    } else {
        actorId = func_ov001_02091834(NULL, 0, kind, object, owner, shapeParams);
    }
    actor = GetStageActor_0209c040((s16)actorId);
    if (actor != NULL && shapeParams != NULL) {
        actor->shapeSize = shapeParams->size;
    }
    if (setup->kind != 4 && setup->kind != 3 && index == 0 && setup->linkTarget != 0) {
        actor->drawFlags |= 0x400;
        actor->linkTarget = setup->linkTarget;
    }
    if (setup->kind == 3) {
        actor->anim = MakeSpawnPair(0, 0x1a);
    } else {
        actor->anim = MakeSpawnPair(0, 0x17);
    }
    actor->alpha = 0x3e;
    actor->mass = record->mass;
    actor->unk_294 = 0;
    actor->spawnB = record->spawnB;
    actor->unk_3a4 = 0;
    actor->unk_3a8 = 0xffff;
    actor->variant = index;
    actor->radius = shape != NULL ? shape->radius : 0;
    actor->mirrored = params->mirrored;
    actor->layer = params->layer;
    actor->trigger = setup->trigger;
    actor->noFloor = record->noFloor != 0;
    actor->hidden = params->hidden;
    if (setup->heavy) {
        actor->mass = 0x7fffffff;
    }
    if (setup->solid) {
        actor->behaviorFlags |= 0x100;
    }
    if (setup->kind == 4) {
        actor->heavy = 1;
    }
    if (setup->kind == 4) {
        actor->behaviorFlags |= 0x80000;
    }
    if (actor->trigger != 0) {
        actor->drawFlags |= 0x10;
    }
    if (index != 0) {
        actor->drawFlags &= ~0x10;
    }
    if (record->hidden) {
        actor->drawFlags &= ~0x10;
    }
    if (actor->hidden) {
        objectRecord = GetStageObjectRecord_0209c0a0(actor->recordId);
        if (objectRecord != NULL) {
            OS_SNPrintf_02002468(path, sizeof(path), data_ov001_020a02e4, objectRecord->variant - 1);
            actor->message = Msg_OpenContainerAndReadHeader_0202cc6c(path, 0xb, 0);
            if (actor->message == NULL) {
                return 0;
            }
        }
    }
    visible = 1;
    if (setup->kind == 4) {
        visible = 0;
    }
    if (record->static_) {
        visible = 0;
    }
    if (setup->heavy) {
        visible = 0;
    }
    actor->visibility = visible;
    if (record->actorId == 0) {
        record->actorId = actorId;
    }
    count = GetGroupResourceCount(entry, index);
    i = 0;
    if (count != 0) {
        do {
            resource = GetGroupResource(entry, index, i);
            if (resource != NULL) {
                AttachActorResource_020914b8(actor, (const char *)func_ov001_0208f018((u8 *)entry->file, resource->nameIndex), resource->isDefault, resource->visible);
            }
        } while (++i < count);
    }
    colliders = GetGroupColliders(entry, index, 0);
    if (colliders != NULL) {
        for (i = 0; i < colliders->count; i++) {
            collider = GetGroupCollider(entry, index, i);
            if (collider != NULL) {
                AttachActorCollider_020912a8(actor, collider, (const char *)func_ov001_0208f018((u8 *)entry->file, collider->nameIndex));
            }
        }
    }
    SetLinkedActorsInQuadTree_020917d8(actor, TRUE);
    return actorId;
}
