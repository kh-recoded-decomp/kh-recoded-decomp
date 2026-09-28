#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0xf];
    u8 packedEntry[0x1c];
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void PackNamedRecordEntry_0204f63c(u8 *out, int index, int nameId);

void PackSelectionRecordEntry_0204fda4(u32 selectionIndex, int nameId, int entryIndex)
{
    PackNamedRecordEntry_0204f63c(GetOverlaySelectionRecord_0204f768(selectionIndex)->packedEntry, entryIndex, nameId);
}
