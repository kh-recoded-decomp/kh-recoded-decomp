#pragma opt_propagation off
#ifndef KH_RECODED_MENU_RECORD_CATEGORIES_H
#define KH_RECODED_MENU_RECORD_CATEGORIES_H

#include "nitro/types.h"


extern const u8 gMenuRecordCategoryCounts[20];

extern const u16 gMenuRecordCategoryFlagBitOffsets_0206adb4[21];

int GetCategoryDisplayRecordId(int category, int oneBasedIndex, int includeLocked);

#endif

#ifndef KH_RECODED_RECORD_CATEGORY_ICONS_H
#define KH_RECODED_RECORD_CATEGORY_ICONS_H

#include "nitro/fx_types.h"

typedef struct RecordIconOffset {
    fx32 x;
    fx32 y;
} RecordIconOffset;


typedef struct RecordCategoryIconEntry {
    u16 metadata00;
    u8 metadata02;
    s8 xOffset;
    s8 yOffset;
    u8 metadata05;
} RecordCategoryIconEntry;

void GetRecordCategoryIconOffset_02069df8(int category, int index, RecordIconOffset *out);

#endif


extern const RecordCategoryIconEntry data_ov002_0206af5c[];

void GetRecordCategoryIconOffset_02069df8(int category, int index, RecordIconOffset *out)
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
        slot = gMenuRecordCategoryFlagBitOffsets_0206adb4[category];
        slot += index;
        shift = 12;
    }
    icon = &data_ov002_0206af5c[slot];
    out->x = -icon->xOffset << shift;
    out->y = -icon->yOffset << shift;
}
