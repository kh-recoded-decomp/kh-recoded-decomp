#include "nitro/types.h"
#include "src/overlays/ov001/StageActorTables.h"

/* One section of a stage resource bank: a counted array of fixed-size records. */
typedef struct OwnerSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} OwnerSection;

typedef struct OwnerTable {
    OwnerSection sections[18];
} OwnerTable;

typedef struct OwnerBank {
    u8 pad_00[8];
    OwnerTable *table;
} OwnerBank;

typedef struct StageEntry {
    u8 pad_00[4];
    OwnerBank *bank;
} StageEntry;

/* Section 0: how the group spawns. */
typedef struct SpawnHeader {
    u32 linkedId;
    u32 modelId;
    u8 isLarge;
    u8 pad_09;
    u8 alwaysVisible;
    u8 pad_0b[0xd];
    u8 variant;
} SpawnHeader;

/* Section 4: the parameters of one group member. */
typedef struct MemberParams {
    u8 pad_00[0x14];
    u8 solid;
    u8 role;
    u8 targetable;
} MemberParams;

/* Section 7: one collider. */
typedef struct ColliderDesc {
    u8 pad_00[4];
    u32 nameIndex;
    u8 pad_08[4];
    u32 shapeFlags;
} ColliderDesc;

/* Section 2: one model resource to attach. */
typedef struct ResourceRef {
    u32 nameIndex;
    u8 isDefault;
    u8 visible;
} ResourceRef;

/* Section 13: how many colliders a member has. */
typedef struct ColliderSet {
    u8 pad_00[4];
    u32 count;
} ColliderSet;

/* Section 17: where each member after the first starts in the other sections. */
typedef struct MemberGroup {
    u8 pad_00[4];
    u16 firstResource;
    u8 pad_06[8];
    u16 firstCollider;
    u8 pad_10[0xa];
    u16 colliderSet;
} MemberGroup;

typedef struct Spawner {
    u8 pad_00[0xa];
    u8 noCollide;
    u8 pad_0b[3];
    u16 slotBase;
    u16 firstActorId;
    u8 pad_12[8];
    u16 recordIndex;
    u8 pad_1c[0x2c];
    s32 drawRange;
    s32 shadowRange;
    u8 pad_50[0x11];
    u8 flipped;
    u8 hideShadow;
} Spawner;

typedef struct ActorState {
    s32 mode;
    s32 kind;
} ActorState;

typedef struct StageActor {
    u8 pad_000[8];
    u16 flags;
    u8 pad_00a[0x184 - 0xa];
    ActorState state;
    u8 pad_18c[0x1c0 - 0x18c];
    u32 linkedId;
    u8 pad_1c4[0x26c - 0x1c4];
    u32 renderFlags : 31;
    u32 pad26c_31 : 1;
    u8 pad_270[0x27e - 0x270];
    u16 recordId;
    u8 pad_280[0x288 - 0x280];
    u16 role : 2;
    u16 castShadow : 2;
    u16 pad288_4 : 5;
    u16 solid : 1;
    u16 pad288_10 : 5;
    u16 boss : 1;
    u16 pad28a_0 : 14;
    u16 targetable : 1;
    u16 flipped : 1;
    u16 member : 3;
    u16 pad28c_3 : 13;
    u8 pad_28e[0x294 - 0x28e];
    s32 shadowTimer;
    s32 shadowRange;
    u8 pad_29c[0x2b0 - 0x29c];
    u32 modelId;
    u32 shapeFlags;
    u8 pad_2b8[4];
    u32 shapeParam;
    u8 pad_2c0[0x2e5 - 0x2c0];
    u8 alpha;
    u8 pad_2e6[0x398 - 0x2e6];
    s32 drawRange;
    u8 pad_39c[0x3a4 - 0x39c];
    u16 animFrame;
    u8 pad_3a6[2];
    u16 animId;
    u8 pad_3aa[0x3c4 - 0x3aa];
    u32 messages;
} StageActor;

typedef struct SmallRecord {
    u8 pad_00;
    u8 actorVariant;
} SmallRecord;

typedef struct ShapeParams {
    u8 pad_00[4];
    u32 param;
} ShapeParams;

typedef struct StageObjectRecord {
    u8 pad_00[0x114];
    u16 messageId;
} StageObjectRecord;

extern const char sOv001_EnAmFormat04dAp2_020a0304[];

extern SmallRecord *GetSmallTableEntry(int index);
extern ShapeParams *GetCollisionShapeParams(ColliderDesc *source, void *params);
extern u16 FindStageObjectByOwner(u16 slot, u32 owner);
extern u16 GetStageRowIndex(Spawner *spawner);
extern int CreateStageActor(StageActorDescriptor *def, u16 ownerId, u16 variant, u16 group, u16 mode,
                            ShapeParams *extra);
extern StageActor *GetStageActor(int id);
extern StageObjectRecord *GetStageObjectRecord(u32 id);
extern int OS_SNPrintf(char *dst, u32 len, const char *fmt, ...);
extern u32 Msg_OpenContainerAndReadHeader(const char *path, u32 heapId, u32 flags);
extern const char *func_ov001_0208f040(OwnerBank *bank, u32 nameIndex);
extern void AttachActorResource(StageActor *actor, const char *name, int isDefault, int visible);
extern void AttachActorCollider(StageActor *actor, ColliderDesc *collider, const char *name);
extern void SetLinkedActorsInQuadTree(StageActor *actor, BOOL insert);

static inline u32 GetSectionCount(StageEntry *owner, int index)
{
    if (owner == NULL) {
        return 0;
    }
    if (owner->bank == NULL) {
        return 0;
    }
    return owner->bank->table->sections[index].count;
}

static inline void *GetSectionElement(StageEntry *owner, int index, u32 element)
{
    OwnerTable *table;
    u32 count;
    u8 *data;

    if (owner == NULL) {
        return NULL;
    }
    if (owner->bank == NULL) {
        return NULL;
    }
    count = GetSectionCount(owner, index);
    table = owner->bank->table;
    data = table->sections[index].data;
    if (count == 0) {
        return NULL;
    }
    if (element >= count) {
        return NULL;
    }
    return data + element * table->sections[index].stride;
}

static inline MemberGroup *GetMemberGroup(StageEntry *owner, u16 index)
{
    return GetSectionElement(owner, 17, index);
}

static inline ColliderDesc *GetColliderDesc(StageEntry *owner, u16 index)
{
    return GetSectionElement(owner, 7, index);
}

static inline ResourceRef *GetResourceRef(StageEntry *owner, u16 index)
{
    return GetSectionElement(owner, 2, index);
}

static inline MemberParams *GetMemberParams(StageEntry *owner, u16 index)
{
    MemberParams *params = GetSectionElement(owner, 4, index);

    return params;
}

static inline ColliderSet *GetColliderSet(StageEntry *owner, u16 index)
{
    return GetSectionElement(owner, 13, index);
}

/* How many resources a member attaches: the gap between its group entry and the previous one. */
static inline int GetMemberResourceCount(StageEntry *owner, u16 member)
{
    MemberGroup *previous;
    MemberGroup *group;

    if (member == 0) {
        group = GetSectionElement(owner, 17, member);
        if (group != NULL) {
            return group->firstResource;
        }
    } else {
        previous = GetMemberGroup(owner, member - 1);
        group = GetSectionElement(owner, 17, member);
        if (previous != NULL && group != NULL) {
            return group->firstResource - previous->firstResource;
        }
    }
    return 0;
}

static inline ActorState MakeActorState(s32 mode, s32 kind)
{
    ActorState state;

    state.mode = mode;
    state.kind = kind;
    return state;
}

/*
 * Creates the actor of one member of a spawner's group from the spawner's resource bank: its
 * collider shape, draw and shadow settings, its message container when it can be targeted, and
 * the model resources and colliders listed for it. Member 0 is the group's main actor.
 */
int SpawnStageGroupMember(Spawner *spawner, StageEntry *owner, u16 member, u16 mode)
{
    ShapeParams *shape;
    MemberParams *params;
    ColliderSet *set;
    u32 first;
    int actorId;
    ColliderDesc *collider;
    u16 count;
    MemberGroup *memberGroup;
    StageActor *actor;
    u16 ownerSlot;
    u16 i;
    SpawnHeader *header;
    u8 variant = 0;
    u8 shapeBuffer[0x14];
    char path[0x40];
    BOOL castShadow;

    if (spawner->recordIndex != 0xffff) {
        SmallRecord *record = GetSmallTableEntry(spawner->recordIndex);

        if (record != NULL) {
            variant = record->actorVariant;
        }
    }
    if (owner == NULL) {
        return 0;
    }
    header = GetSectionElement(owner, 0, 0);
    if (header == NULL) {
        return 0;
    }

    /* Member 0 starts at the first entry of each section; the others where their group entry says. */
    first = 0;
    if (member != 0) {
        memberGroup = GetMemberGroup(owner, member - 1);
        if (memberGroup == NULL) {
            collider = NULL;
            goto have_collider;
        }
        first = memberGroup->firstCollider;
    }
    collider = GetColliderDesc(owner, first);
have_collider:
    params = GetMemberParams(owner, member);
    if (params == NULL) {
        return 0;
    }
    shape = GetCollisionShapeParams(collider, shapeBuffer);
    ownerSlot = FindStageObjectByOwner(member + spawner->slotBase * 100, 0);
    if (ownerSlot == 0) {
        return 0;
    }
    if (member == 0) {
        actorId = CreateStageActor(&gStageObjectActorDescriptor, GetStageRowIndex(spawner), variant, ownerSlot, mode,
                                   shape);
    } else {
        actorId = CreateStageActor(NULL, 0, variant, ownerSlot, mode, shape);
    }
    actor = GetStageActor((s16)actorId);
    if (actor != NULL && shape != NULL) {
        actor->shapeParam = shape->param;
    }
    if (header->variant != 4 && header->variant != 3 && member == 0 && header->linkedId != 0) {
        actor->flags |= 0x400;
        actor->linkedId = header->linkedId;
    }
    if (header->variant == 3) {
        actor->state = MakeActorState(0, 0x1a);
    } else {
        actor->state = MakeActorState(0, 0x17);
    }
    actor->alpha = 0x3e;
    actor->drawRange = spawner->drawRange;
    actor->shadowTimer = 0;
    actor->shadowRange = spawner->shadowRange;
    actor->animFrame = 0;
    actor->animId = 0xffff;
    actor->member = member;
    actor->shapeFlags = collider != NULL ? collider->shapeFlags : 0;
    actor->solid = params->solid;
    actor->role = params->role;
    actor->modelId = header->modelId;
    actor->flipped = spawner->flipped != 0;
    actor->targetable = params->targetable;
    if (header->alwaysVisible) {
        actor->drawRange = 0x7fffffff;
    }
    if (header->isLarge) {
        actor->renderFlags |= 0x100;
    }
    if (header->variant == 4) {
        actor->boss = TRUE;
    }
    if (header->variant == 4) {
        actor->renderFlags |= 0x80000;
    }
    if (actor->modelId != 0) {
        actor->flags |= 0x10;
    }
    if (member != 0) {
        actor->flags &= 0xffef;
    }
    if (spawner->noCollide) {
        actor->flags &= 0xffef;
    }
    if (actor->targetable) {
        StageObjectRecord *record = GetStageObjectRecord(actor->recordId);

        if (record != NULL) {
            OS_SNPrintf(path, sizeof(path), sOv001_EnAmFormat04dAp2_020a0304, record->messageId - 1);
            actor->messages = Msg_OpenContainerAndReadHeader(path, 0xb, 0);
            if (actor->messages == 0) {
                return 0;
            }
        }
    }
    castShadow = header->variant != 4;
    if (spawner->hideShadow) {
        castShadow = FALSE;
    }
    if (header->alwaysVisible) {
        castShadow = FALSE;
    }
    actor->castShadow = castShadow;
    if (spawner->firstActorId == 0) {
        spawner->firstActorId = actorId;
    }

    count = GetMemberResourceCount(owner, member);
    for (i = 0; i < count; i++) {
        ResourceRef *ref;

        first = 0;
        if (member != 0) {
            memberGroup = GetMemberGroup(owner, member - 1);
            if (memberGroup == NULL) {
                ref = NULL;
                goto have_ref;
            }
            first = memberGroup->firstResource;
        }
        ref = GetResourceRef(owner, first + i);
    have_ref:
        if (ref != NULL) {
            AttachActorResource(actor, func_ov001_0208f040(owner->bank, ref->nameIndex), ref->isDefault, ref->visible);
        }
    }

    first = 0;
    if (member != 0) {
        memberGroup = GetMemberGroup(owner, member - 1);
        if (memberGroup == NULL) {
            set = NULL;
            goto have_set;
        }
        first = memberGroup->colliderSet;
    }
    set = GetColliderSet(owner, first);
have_set:
    if (set != NULL) {
        for (i = 0; i < set->count; i++) {
            ColliderDesc *part;

            first = 0;
            if (member != 0) {
                memberGroup = GetMemberGroup(owner, member - 1);
                if (memberGroup == NULL) {
                    part = NULL;
                    goto have_part;
                }
                first = memberGroup->firstCollider;
            }
            part = GetColliderDesc(owner, first + i);
        have_part:
            if (part != NULL) {
                AttachActorCollider(actor, part, func_ov001_0208f040(owner->bank, part->nameIndex));
            }
        }
    }
    SetLinkedActorsInQuadTree(actor, TRUE);
    return actorId;
}
