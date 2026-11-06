#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *objManager;
} PopupManager;

extern PopupManager *gTrophyPopupWorkStorage;
extern void SetIndexedRecordAnimationFrame(void *objManager, int slotIndex, int value);
extern int IndexedRecord_SetActive(void *objManager, int slotIndex);
extern void IndexedRecord_ClearActive(void *objManager, int slotIndex);
extern void IndexedRecords_SetFlag2(void *objManager, int slotIndex, int value);

void SetPopupSlotVisible_020c319c(int slotIndex, BOOL visible)
{
    void *objManager = gTrophyPopupWorkStorage->objManager;

    if (visible) {
        SetIndexedRecordAnimationFrame(objManager, slotIndex, 0);
        IndexedRecord_SetActive(objManager, slotIndex);
    } else {
        IndexedRecord_ClearActive(objManager, slotIndex);
    }
    IndexedRecords_SetFlag2(objManager, slotIndex, visible);
}
