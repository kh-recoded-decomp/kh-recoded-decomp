#ifndef KH_RECODED_RECORD_CATEGORY_ICONS_H
#define KH_RECODED_RECORD_CATEGORY_ICONS_H

#include "nitro/fx_types.h"

typedef struct RecordIconOffset {
    fx32 x;
    fx32 y;
} RecordIconOffset;

/* Only the signed offsets are interpreted by this helper. */
typedef struct RecordCategoryIconEntry {
    u16 metadata00;
    u8 metadata02;
    s8 xOffset;
    s8 yOffset;
    u8 metadata05;
} RecordCategoryIconEntry;

void GetRecordCategoryIconOffset(int category, int index, RecordIconOffset *out);

#endif
