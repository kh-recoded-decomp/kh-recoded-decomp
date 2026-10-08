#include "nitro/types.h"

typedef struct {
    u32 enabled : 1;
    u32 blocked : 1;
    u32 checkKind : 1;
} UseFlags;

typedef struct {
    u8 kind;
    u8 groupId;
    u8 slotId;
} HandleSlot;

typedef struct {
    u8 pad_00[0x194];
    HandleSlot slot;
} HandleInfo;

typedef struct {
    u8 pad_00[0x50];
    s32 mode;
} HandleOwner;

typedef struct {
    u8 pad_00[0x14];
    HandleInfo *info;
    u8 pad_18[0x50];
    HandleOwner *owner;
    s32 type;
} HandleObject;

typedef struct {
    u8 pad_00[0x5a];
    u8 category;
} EntryDef;

typedef struct {
    u32 pad_00;
    EntryDef *def;
} LinkedEntry;

typedef struct {
    HandleObject *obj;
    s32 state;
} ObjHandle;

extern LinkedEntry *func_ov001_02087224(u8 groupId, u8 slotId);
extern int Object_GetKindValue_0208744c(LinkedEntry *entry);

#pragma opt_propagation off
BOOL IsObjHandleUsable_020a9268(ObjHandle *handle, int unused, UseFlags *flags)
{
    BOOL result = TRUE;
    HandleSlot *slot;
    LinkedEntry *entry;
    BOOL ok;

    if (handle->state == 4) {
        slot = &handle->obj->info->slot;
        if (slot->kind == 1) {
            ok = FALSE;
            if (handle->obj->type != 0x19) {
                if (handle->obj->type == 0x1a) {
                    ok = result;
                }
            } else if (!flags->blocked) {
                ok = result;
            }
            if (!ok) {
                result = FALSE;
            } else if (flags->enabled) {
                result = FALSE;
            }
        } else if (slot->kind == 4) {
            entry = func_ov001_02087224(slot->groupId, slot->slotId);
            switch (entry->def->category) {
            case 1:
            case 7:
                if (flags->enabled) {
                    result = FALSE;
                } else {
                    result = TRUE;
                }
                break;
            case 4:
                if ((s16)handle->obj->owner->mode != 2 && flags->enabled) {
                    result = FALSE;
                }
                break;
            }
            if (flags->checkKind && Object_GetKindValue_0208744c(entry) == 3) {
                result = FALSE;
            }
        }
    }
    return result;
}