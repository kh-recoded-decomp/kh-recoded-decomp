#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldManager {
    u8 pad_00[0x59];
    u8 listId;
} FieldManager;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldManager *manager;
    u8 pad_08[4];
    void *onQuery;
    u8 shape[0x20];
    u16 statusFlags;
    u8 slot;
    u8 pad_33;
    fx32 speed;
    VecFx32 position;
    u16 dropGroup;
    u8 dropIndex;
    u8 animIndex;
    s8 dropVariant;
    s8 dropItem;
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    fx32 overflow;
    s32 kind : 16;
    s32 subKind : 12;
    s32 bit28 : 1;
    s32 hitsLeft : 3;
    VecFx32 home;
    int field_60;
    int field_64;
    s32 timer;
    s16 eventId;
    s16 pendingEvent;
} FieldObject;

extern FieldObject *func_ov001_02086308(void *pool, int kind);
extern int GetEntryUnlockState_02087478(BOOL skipModeCheck, u32 flagOffset, u32 entryId, u32 slot);
extern void func_ov001_020645dc(int objectId);
extern void func_ov017_020a3610(void);
extern void AppendNodeToActiveList_02086fac(u32 listId, u32 kind, u8 tag);

u8 SpawnFieldObject_020a3ae8(void *pool, int kind, int slot, u16 objectId, u8 dropIndex, VecFx32 *position,
                             s8 dropVariant, s8 dropItem, s16 eventId, int mode, fx32 speed, int modeParam)
{
    FieldObject *object = func_ov001_02086308(pool, kind);
    FieldManager *manager = object->manager;
    BOOL active;

    object->position = *position;
    object->dropGroup = objectId;
    object->dropIndex = dropIndex;
    object->animIndex = 0;
    object->speed = speed;
    object->home = *position;
    object->state = 0;
    object->flags = 0;
    object->dropVariant = dropVariant;
    object->dropItem = dropItem;
    object->kind = mode;
    object->field_60 = 0;
    object->field_64 = 0;
    object->subKind = modeParam;
    object->timer = -1;
    object->bit28 = 1;
    object->overflow = 0;
    object->hitsLeft = 1;
    if (mode == 10) {
        if (!GetEntryUnlockState_02087478(FALSE, dropItem, objectId, dropIndex)) {
            object->kind = 10;
            object->hitsLeft = 2;
        } else {
            object->kind = 1;
        }
    }
    if (object->dropVariant != -1 && object->dropItem < 0) {
        func_ov001_020645dc(objectId);
    }
    object->eventId = eventId;
    object->pendingEvent = -1;
    object->flags |= 1;
    active = TRUE;
    if (object->state != 2 && object->state != 1) {
        active = FALSE;
    }
    if (active) {
        object->onQuery = NULL;
        object->state = 2;
    } else {
        object->onQuery = func_ov017_020a3610;
        object->statusFlags |= 0x10;
    }
    object->slot = slot;
    AppendNodeToActiveList_02086fac(manager->listId, kind, object->slot);
    return object->slot;
}
