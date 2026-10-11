#ifndef KH_RECODED_PAGE_VARIANT_TABLE_H
#define KH_RECODED_PAGE_VARIANT_TABLE_H

#include "nitro/types.h"

typedef struct PageRecordVariant {
    s16 recordId;
    u8 level;
    u8 colorIndex;
} PageRecordVariant;

typedef struct PageVariantEntry {
    u8 pageIndex;
    u8 titleIndex;
    PageRecordVariant primary[3];
    PageRecordVariant secondary[3];
} PageVariantEntry;

typedef struct PageVariantTable {
    PageVariantEntry entries[5];
    u16 terminator;
} PageVariantTable;

typedef char PageVariantEntrySizeCheck[sizeof(PageVariantEntry) == 26 ? 1 : -1];
typedef char PageVariantTableSizeCheck[sizeof(PageVariantTable) == 132 ? 1 : -1];

extern const PageVariantTable gPageVariantTable;

#endif
