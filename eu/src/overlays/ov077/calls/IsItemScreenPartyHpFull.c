#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 current;
    u16 required;
} OverlaySelectionRecord;

extern u8 gSelectionRuntimeHeader;
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

BOOL IsItemScreenPartyHpFull(void)
{
    BOOL allComplete = TRUE;
    int index;

    for (index = 0; index < gSelectionRuntimeHeader; index++) {
        OverlaySelectionRecord *record = GetOverlaySelectionRecord(index);
        if (record->current < record->required) {
            allComplete = FALSE;
            break;
        }
    }
    return allComplete;
}
