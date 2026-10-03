#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
} OverlaySelectionRecord;

extern OverlaySelectionRecord *func_0204f768(u32 selectionIndex);
extern VecFx32 data_ov021_020b4ea8[][9];

void GetSelectionSlotPosition_020a91b8(VecFx32 *out, u32 selectionIndex, int slot)
{
    OverlaySelectionRecord *record = func_0204f768(selectionIndex);
    *out = data_ov021_020b4ea8[record->overlaySet][slot];
}
