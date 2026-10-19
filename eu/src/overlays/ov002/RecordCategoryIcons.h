#ifndef KH_RECODED_RECORD_CATEGORY_ICONS_H
#define KH_RECODED_RECORD_CATEGORY_ICONS_H

#include "nitro/fx_types.h"

typedef struct RecordIconOffset {
    fx32 x;
    fx32 y;
} RecordIconOffset;

/* A contiguous span of avatar resources and its signed display offsets. */
typedef struct RecordCategoryIconEntry {
    s16 firstEntry;
    s8 entryCount;
    s8 xOffset;
    s8 yOffset;
    u8 reserved05;
} RecordCategoryIconEntry;

typedef char RecordCategoryIconEntrySizeCheck[
    sizeof(RecordCategoryIconEntry) == 6 ? 1 : -1];

extern const RecordCategoryIconEntry gMenuRecordIconLayouts[816];

void GetRecordCategoryIconOffset(int category, int index, RecordIconOffset *out);

#endif
