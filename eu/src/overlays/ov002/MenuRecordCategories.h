#ifndef KH_RECODED_MENU_RECORD_CATEGORIES_H
#define KH_RECODED_MENU_RECORD_CATEGORIES_H

#include "nitro/types.h"

/* Overlay-local copies of the record category counts and flag offsets. */
extern const u8 gMenuRecordCategoryCounts[20];
/* The final offset is the end of the bit range (815 bits). */
extern const u16 gMenuRecordCategoryFlagBitOffsets[21];

int GetCategoryDisplayRecordId(int category, int oneBasedIndex, int includeLocked);

#endif
