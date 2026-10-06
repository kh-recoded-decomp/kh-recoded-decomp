#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 current;
    u16 required;
} OverlaySelectionRecord;

extern u8 data_020608c8;
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

BOOL func_ov076_020caa34(void)
{
    BOOL allComplete = TRUE;
    int index;

    for (index = 0; index < data_020608c8; index++) {
        OverlaySelectionRecord *record = GetOverlaySelectionRecord(index);
        if (record->current < record->required) {
            allComplete = FALSE;
            break;
        }
    }
    return allComplete;
}
