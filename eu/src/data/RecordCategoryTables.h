#ifndef KH_RECODED_RECORD_CATEGORY_TABLES_H
#define KH_RECODED_RECORD_CATEGORY_TABLES_H

#include "nitro/types.h"

/* Categories are stored as one-based values in the record metadata. */
extern const u8 gRecordCategoryCounts[20];
extern const u16 gRecordCategoryFlagBitOffsets[20];
extern const s32 gRecordCategoryFirstIds[20];
extern const s32 gStartingRecordIds[11];
extern const s32 gRandomRecordExclusions[19];

#endif
