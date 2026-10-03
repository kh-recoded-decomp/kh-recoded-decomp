#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventTargetInfo {
    u16 id;
    u16 isPartner : 1;
    u16 isLocked : 1;
    u16 isScripted : 1;
    u16 isHidden : 1;
    u16 isVisible : 1;
    u16 unk_02_5 : 11;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct StageEventRecord {
    s32 type;
    u8 pad_04[2];
    u16 unk_06_0 : 11;
    u16 forceHidden : 1;
    u16 unk_06_12 : 4;
    u8 pad_08;
    u8 mode;
    u8 pad_0a[4];
    u16 objectId;
    u16 actorId;
    u16 handleId;
    u16 entryId;
    u8 pad_16[0x62 - 0x16];
    u8 locked;
    u8 pad_63[0x6c - 0x63];
    u8 kind;
    u8 pad_6d[3];
    fx32 width;
    fx32 height;
} StageEventRecord;

typedef struct PartySlot {
    u16 id;
    u8 pad_02[0xa];
    VecFx32 position;
} PartySlot;

typedef struct StageActor {
    u8 pad_000[0xb8];
    VecFx32 position;
    u8 pad_0c4[0x288 - 0xc4];
    u16 unk_288_0 : 4;
    u16 hidden : 1;
    u16 unk_288_5 : 11;
} StageActor;

typedef struct TargetItem {
    fx32 height;
} TargetItem;

typedef struct TargetTable {
    u8 pad_00[4];
    u32 count;
    u32 stride;
    TargetItem *items;
} TargetTable;

typedef struct StageResource {
    u8 pad_00[8];
    TargetTable *table;
} StageResource;

typedef struct StageEntry {
    u8 pad_00[4];
    StageResource *resource;
} StageEntry;

typedef struct LargeTableEntry {
    u8 pad_00;
    u8 owner;
} LargeTableEntry;

extern s32 data_ov001_0209f2c8;
extern void func_01ff8830(void *dst, int value, u32 size);
extern StageEventRecord *GetStageEventRecord_0209c0ec(u32 id);
extern PartySlot *FindPartySlotById_0209d19c(u32 id);
extern StageActor *GetStageActor_0209c040(s16 id);
extern u16 RemapExtendedSlotId_0209d03c(u16 id);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern StageEntry *GetStageEntry_0209c074(s16 id);
extern u16 *GetStageObjectHandle_0209c0c4(u16 id);
extern LargeTableEntry *GetLargeTableEntry_0209c30c(u16 id);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);

static inline int GetSessionMode(void)
{
    if (!Session_Exists_02063a24()) {
        return 0;
    }
    return func_ov001_02063a38();
}

static inline u32 GetTargetCount(StageEntry *entry)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->resource == NULL) {
        return 0;
    }
    return entry->resource->table->count;
}

static inline TargetItem *GetTarget(StageEntry *entry, u32 index)
{
    StageResource *resource;
    u32 count;
    u8 *items;

    if (entry == NULL) {
        return NULL;
    }
    resource = entry->resource;
    if (resource == NULL) {
        return NULL;
    }
    count = GetTargetCount(entry);
    items = (u8 *)resource->table->items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (TargetItem *)(items + index * resource->table->stride);
}

BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out)
{
    StageEventRecord *record;
    StageActor *actor;

    func_01ff8830(out, 0, sizeof(EventTargetInfo));
    if (data_ov001_0209f2c8 != -1) {
        record = GetStageEventRecord_0209c0ec(id);
        if (record == NULL) {
            return FALSE;
        }
        if (record->objectId == 0x63) {
            PartySlot *slot;

            if (record->width > 0 && (slot = FindPartySlotById_0209d19c(id)) != NULL) {
                out->id = slot->id;
                out->isPartner = 1;
                out->isLocked = 0;
                out->isScripted = 0;
                out->position = slot->position;
                out->width = record->width >> 12;
                out->height = record->height >> 12;
                out->displayHeight = out->height;
                out->displayWidth = out->width;
                out->kind = 1;
                return TRUE;
            }
            return FALSE;
        }
        if (record->actorId == 0) {
            return FALSE;
        }
        actor = GetStageActor_0209c040(record->actorId);
        if (actor == NULL) {
            return FALSE;
        }
        out->id = RemapExtendedSlotId_0209d03c(record->objectId);
        out->isPartner = record->mode == 4;
        out->isLocked = record->mode == 3;
        if (out->isPartner && record->locked) {
            out->isLocked = 1;
        }
        out->isScripted = record->type == 4;
        out->isHidden = record->forceHidden || record->type == 0xb;
        out->isVisible = !actor->hidden;
        out->position = actor->position;
        out->width = record->width >> 12;
        out->height = record->height >> 12;
        out->kind = record->kind;
        if (record->width > 0 && record->width < 0x1000) {
            out->width = 1;
        }
        if (record->height > 0 && record->height < 0x1000) {
            out->height = 1;
        }
        if (GetSessionMode() == 7 && record->entryId != 0) {
            StageEntry *entry = GetStageEntry_0209c074(record->entryId);
            if (entry != NULL) {
                TargetItem *item = GetTarget(entry, 0);
                if (item != NULL) {
                    out->position.y += item->height >> 1;
                }
            }
        }
        if (GetSessionMode() == 6 && record->handleId != 0) {
            u16 *handle = GetStageObjectHandle_0209c0c4(record->handleId);
            if (handle != NULL) {
                out->isPartner = GetLargeTableEntry_0209c30c(*handle)->owner == 1;
            }
        }
        if (out->isLocked || record->locked) {
            out->displayWidth = FX_Div_01ff9c84(record->width, record->height) * 200 >> 12;
            out->displayHeight = 200;
        } else {
            out->displayWidth = out->width;
            out->displayHeight = out->height;
        }
        return TRUE;
    }
    return FALSE;
}


