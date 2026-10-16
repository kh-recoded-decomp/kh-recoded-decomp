#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkArray {
    u32 count;
    u32 stride;
    u8 *items;
} LinkArray;

typedef struct LinkTable {
    u8 unknown00[0x84];
    LinkArray paths;
    u8 unknown90[0xe4 - 0x90];
    LinkArray slots;
    u8 unknownf0[0x114 - 0xf0];
    LinkArray variants;
} LinkTable;

typedef struct LinkData {
    u8 unknown00[8];
    LinkTable *table;
} LinkData;

typedef struct StageLink {
    u32 unknown00;
    LinkData *data;
} StageLink;

typedef struct LinkVariant {
    u8 unknown00[0x1c];
    u16 slotOffset;
} LinkVariant;

typedef struct LinkSlot {
    u32 pathIndex;
} LinkSlot;

typedef struct LinkPath {
    u32 unknown00;
    s32 nodeNameIndex;
    VecFx32 offset;
    u8 unknown14[0x24 - 0x14];
    s32 objectId;
    s32 spawnArg;
} LinkPath;

typedef struct StageEvent {
    u8 unknown00[0xe];
    u16 linkId;
} StageEvent;

typedef struct StageController {
    u8 unknown00[0xa];
    u16 eventId;
    s16 actorId;
} StageController;

typedef struct StageActor {
    u8 unknown00[0x1d2];
    u16 eventId;
    u8 unknown1d4[0x270 - 0x1d4];
    u16 spawnArg;
    u8 unknown272[0x28c - 0x272];
    u16 variant : 3;
    u16 otherCellBits : 13;
    u8 unknown28e[0x2c0 - 0x28e];
    VecFx32 position;
    u8 unknown2cc[0x3b0 - 0x2cc];
    s16 relatedActorId;
} StageActor;

typedef struct FieldContext {
    StageEvent *record;
    StageController *controller;
    StageActor *actor;
} FieldContext;

typedef struct TaggedValue {
    s16 tag;
    s16 unknown02;
    s32 value;
} TaggedValue;

typedef struct ScriptCommand {
    TaggedValue column;
    TaggedValue row;
} ScriptCommand;


typedef char LinkArraySize[sizeof(LinkArray) == 12 ? 1 : -1];
typedef char LinkPathsOffset[(u32)&((LinkTable *)0)->paths == 0x84 ? 1 : -1];
typedef char LinkSlotsOffset[(u32)&((LinkTable *)0)->slots == 0xe4 ? 1 : -1];
typedef char LinkVariantsOffset[(u32)&((LinkTable *)0)->variants == 0x114 ? 1 : -1];
typedef char LinkVariantSlotOffset[(u32)&((LinkVariant *)0)->slotOffset == 0x1c ? 1 : -1];
typedef char LinkPathNodeOffset[(u32)&((LinkPath *)0)->nodeNameIndex == 4 ? 1 : -1];
typedef char LinkPathPositionOffset[(u32)&((LinkPath *)0)->offset == 8 ? 1 : -1];
typedef char LinkPathObjectOffset[(u32)&((LinkPath *)0)->objectId == 0x24 ? 1 : -1];
typedef char LinkPathArgumentOffset[(u32)&((LinkPath *)0)->spawnArg == 0x28 ? 1 : -1];
typedef char StageEventLinkOffset[(u32)&((StageEvent *)0)->linkId == 0xe ? 1 : -1];
typedef char ControllerEventOffset[(u32)&((StageController *)0)->eventId == 0xa ? 1 : -1];
typedef char ControllerActorOffset[(u32)&((StageController *)0)->actorId == 0xc ? 1 : -1];
typedef char ActorEventOffset[(u32)&((StageActor *)0)->eventId == 0x1d2 ? 1 : -1];
typedef char ActorSpawnArgumentOffset[(u32)&((StageActor *)0)->spawnArg == 0x270 ? 1 : -1];
typedef char ActorPositionOffset[(u32)&((StageActor *)0)->position == 0x2c0 ? 1 : -1];
typedef char ActorRelatedIdOffset[(u32)&((StageActor *)0)->relatedActorId == 0x3b0 ? 1 : -1];
typedef char FieldContextSize[sizeof(FieldContext) == 12 ? 1 : -1];
typedef char TaggedValueSize[sizeof(TaggedValue) == 8 ? 1 : -1];

extern FieldContext gActiveFieldContext;
extern TaggedValue *ResolveTaggedValueRef(void *thread, TaggedValue *value);
extern StageActor *GetStageActor(int id);
extern StageEvent *GetStageEventRecord(u32 id);
extern void ClearWalkerStepState(StageActor *actor);
extern StageLink *FindStageLink(u32 id);
extern void SetActorGridCell(StageActor *actor, u16 column, u16 row);
extern u16 FindStageObjectByOwner(u16 slot, u32 owner);
extern int ReleaseStageSlot(int slot);
extern StageController *GetStageController(u32 id);
extern int InitStageSpawnRequest(StageController *request, int type, int argument);
extern s32 func_ov001_0208f040(LinkData *data, int index);
extern u16 FindActorResourceIndexByName(StageActor *actor, const char *name);
extern void GetNodePosition(StageActor *actor, u32 node, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void UpdateFieldActorMovement(StageActor *actor);
extern u16 GetStageRowIndex(StageEvent *record);

static inline u32 GetVariantCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->table->variants.count;
}

static inline LinkVariant *GetLinkVariant(StageLink *link, u16 index)
{
    u32 count;
    LinkData *data;
    LinkTable *table;
    u8 *items;
    if (link == NULL) {
        return NULL;
    }
    data = link->data;
    if (data == NULL) {
        return NULL;
    }
    count = GetVariantCount(link);
    table = data->table;
    items = table->variants.items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkVariant *)(items + index * table->variants.stride);
}

static inline u32 GetSlotCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->table->slots.count;
}

static inline LinkSlot *GetSlotElement(LinkTable *table, u32 count, u8 *items, u16 index)
{
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkSlot *)(items + index * table->slots.stride);
}

static inline LinkSlot *GetVariantSlot(StageLink *link, u16 column, u16 variant)
{
    u32 count;
    LinkData *data;
    LinkTable *table;
    u8 *items;
    u16 offset = 0;
    if (variant != 0) {
        LinkVariant *record = GetLinkVariant(link, variant - 1);
        if (record == NULL) {
            return NULL;
        }
        offset = record->slotOffset;
    }
    if (link == NULL) {
        return NULL;
    }
    data = link->data;
    if (data == NULL) {
        return NULL;
    }
    count = GetSlotCount(link);
    table = data->table;
    items = table->slots.items;
    return GetSlotElement(table, count, items, offset + column);
}

static inline u32 GetPathCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->table->paths.count;
}

static inline LinkPath *GetLinkPath(StageLink *link, u16 index)
{
    u32 count;
    LinkData *data;
    LinkTable *table;
    u8 *items;
    if (link == NULL) {
        return NULL;
    }
    data = link->data;
    if (data == NULL) {
        return NULL;
    }
    count = GetPathCount(link);
    table = data->table;
    items = table->paths.items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkPath *)(items + index * table->paths.stride);
}

/* Resolve a variant's slot, place or spawn its actor, and record the scene owner. */
s32 ScriptCmd_SpawnLinkedActor(void *thread, ScriptCommand *command)
{
    TaggedValue *columnValue = ResolveTaggedValueRef(thread, &command->column);
    TaggedValue *rowValue = ResolveTaggedValueRef(thread, &command->row);
    StageEvent *event = gActiveFieldContext.record;
    StageController *controller = gActiveFieldContext.controller;
    StageActor *owner = gActiveFieldContext.actor;
    StageController *spawnController;
    StageActor *actor;
    StageLink *link;
    LinkSlot *slot;
    LinkPath *path;
    s32 column;
    u16 objectId;
    const char *nodeName;

    if (event == NULL && controller != NULL) {
        event = GetStageEventRecord(controller->eventId);
    } else if (owner != NULL) {
        StageActor *related = GetStageActor(owner->relatedActorId);
        if (related != NULL) {
            event = GetStageEventRecord(related->eventId);
        }
    }
    if (event == NULL) {
        return 0;
    }
    if (owner == NULL) {
        return 0;
    }
    if (columnValue->value < 0) {
        ClearWalkerStepState(owner);
        return 0;
    }
    link = FindStageLink(event->linkId);
    if (link == NULL) {
        return 0;
    }
    column = columnValue->value;
    u16 slotColumn = column;
    slot = GetVariantSlot(link, slotColumn, owner->variant);
    if (slot == NULL) {
        return 0;
    }
    path = GetLinkPath(link, slot->pathIndex);
    if (path == NULL) {
        return 0;
    }
    if (path->objectId == 0) {
        SetActorGridCell(owner, column, rowValue->value);
        return 0;
    }
    objectId = FindStageObjectByOwner(path->objectId, 1);
    if (objectId != 0) {
        spawnController = GetStageController(ReleaseStageSlot(4));
        InitStageSpawnRequest(spawnController, (s16)objectId, (u16)path->spawnArg);
        actor = GetStageActor(spawnController->actorId);
        actor->spawnArg = path->spawnArg;
        if (path->nodeNameIndex != 0) {
            nodeName = (const char *)func_ov001_0208f040(link->data, path->nodeNameIndex);
            if (nodeName != NULL) {
                GetNodePosition(owner, FindActorResourceIndexByName(owner, nodeName),
                                &actor->position);
                VEC_Add(&path->offset, &actor->position, &actor->position);
                UpdateFieldActorMovement(actor);
            }
        }
        spawnController->eventId = GetStageRowIndex(event);
        SetActorGridCell(actor, columnValue->value, rowValue->value);
    }
    return 0;
}
