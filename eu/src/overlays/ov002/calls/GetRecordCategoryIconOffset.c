#pragma opt_propagation off

#include "src/overlays/ov002/MenuRecordCategories.h"
#include "src/overlays/ov002/RecordCategoryIcons.h"

void GetRecordCategoryIconOffset(int category, int index, RecordIconOffset *out)
{
    int slot;
    int shift;
    const RecordCategoryIconEntry *icon;
    if (category >= 20)
        category = 16;
    if (category >= 1 && category < 6) {
        out->x = 0;
        out->y = -32768;
        return;
    }
    if (category == 0 || category == 17 || category == 18) {
        slot = 0;
        shift = 11;
    } else {
        slot = gMenuRecordCategoryFlagBitOffsets[category];
        slot += index;
        shift = 12;
    }
    icon = &gMenuRecordIconLayouts[slot];
    out->x = -icon->xOffset << shift;
    out->y = -icon->yOffset << shift;
}
