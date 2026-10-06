#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *objManager;
} PopupManager;

extern PopupManager *data_ov093_020c5104;
extern void func_0204f218(void *objManager, int slotIndex, int value);
extern int IndexedRecord_SetActive(void *objManager, int slotIndex);
extern void IndexedRecord_ClearActive(void *objManager, int slotIndex);
extern void IndexedRecords_SetFlag2(void *objManager, int slotIndex, int value);

void func_ov093_020c319c(int slotIndex, BOOL visible)
{
    void *objManager = data_ov093_020c5104->objManager;

    if (visible) {
        func_0204f218(objManager, slotIndex, 0);
        IndexedRecord_SetActive(objManager, slotIndex);
    } else {
        IndexedRecord_ClearActive(objManager, slotIndex);
    }
    IndexedRecords_SetFlag2(objManager, slotIndex, visible);
}
