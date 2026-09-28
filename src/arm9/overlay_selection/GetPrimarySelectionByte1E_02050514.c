#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0x1d];
    u8 unk_1E;
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);

u8 GetPrimarySelectionByte1E_02050514(void)
{
    return GetOverlaySelectionRecord_0204f768(0)->unk_1E;
}
