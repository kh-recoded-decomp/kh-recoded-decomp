#include "nitro/types.h"

#pragma explicit_zero_data on

typedef struct ResultsShopEntryData {
    u32 itemId;
    u32 cost;
    u8 unlockFlags;
    s8 requiredRank;
    u16 reserved;
} ResultsShopEntryData;

ResultsShopEntryData gResultsShopEntries[23] = {
    {0x0125, 0x00C8, 1, 0, 0},
    {0x0096, 0x00C8, 1, 0, 0},
    {0x009A, 0x00C8, 1, 0, 0},
    {0x0091, 0x0032, 1, 0, 0},
    {0x0091, 0x0032, 0, 0, 0},
    {0x0096, 0x000A, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
    {0x0080, 0x0014, 0, 0, 0},
};
