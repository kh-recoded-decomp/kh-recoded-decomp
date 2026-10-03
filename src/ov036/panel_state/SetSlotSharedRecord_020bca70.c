#include "nitro/types.h"

typedef struct SharedRecord {
    u8 pad_00[0xc];
    int id;
} SharedRecord;

typedef struct SlotEntry {
    u8 pad_00[0x94];
    u32 activeId;
    u32 pendingId;
} SlotEntry;

typedef struct SlotScene {
    u8 pad_0000[0xc80];
    int deferred;
    u8 pad_0c84[0xe7c - 0xc84];
    SharedRecord *record;
    u8 pad_0e80[0x104c - 0xe80];
    int frameBase;
    u8 pad_1050[0x1090 - 0x1050];
    SlotEntry *slots;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3920;
extern int FindOrAcquireOwnerSlot_020bb7c0(int ownerId);
extern BOOL IsRecordIdFree_0202c38c(int id);
extern int AcquireSharedRecord_0202c764(int key, SharedRecord **out, int kind);
extern SharedRecord *RetainOrInitializeSharedRecord_0202c80c(int key, int kind);
extern int ReleaseSharedRecordSlot_0202c8a8(SharedRecord *record);
extern void func_ov036_020bc978(SlotEntry *slot);

BOOL SetSlotSharedRecord_020bca70(int ownerId, u32 recordId)
{
    SlotScene *scene = data_ov036_020c3920.scene;
    SlotEntry *slot = &scene->slots[FindOrAcquireOwnerSlot_020bb7c0(ownerId)];

    if (scene->deferred != 0) {
        if (slot->pendingId == recordId) {
            return TRUE;
        }
    } else if (slot->activeId == recordId) {
        return TRUE;
    }
    for (;;) {
        if (scene->record == NULL) {
            if (scene->deferred != 0) {
                slot->pendingId = recordId;
                return TRUE;
            }
            if (slot->activeId != slot->pendingId) {
                scene->record = RetainOrInitializeSharedRecord_0202c80c((((scene->frameBase + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (recordId & 0x1ff), 0x11);
                func_ov036_020bc978(slot);
                slot->pendingId = recordId;
                slot->activeId = recordId;
                return TRUE;
            }
            AcquireSharedRecord_0202c764((((scene->frameBase + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (recordId & 0x1ff), &scene->record, 0x11);
            break;
        }
        if (scene->deferred != 0) {
            ReleaseSharedRecordSlot_0202c8a8(scene->record);
            scene->record = NULL;
        } else {
            if (IsRecordIdFree_0202c38c(scene->record->id)) {
                func_ov036_020bc978(slot);
                slot->pendingId = recordId;
                slot->activeId = recordId;
                return TRUE;
            }
            break;
        }
    }
    return FALSE;
}
