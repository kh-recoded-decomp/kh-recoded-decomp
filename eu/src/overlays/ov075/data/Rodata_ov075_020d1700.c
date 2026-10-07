#include "nitro/types.h"

typedef struct ThresholdEntry {
    s32 threshold;
    s32 value;
} ThresholdEntry;

typedef struct ThresholdTable {
    ThresholdEntry entries[5];
} ThresholdTable;

const ThresholdTable sLevelRankThresholds = {
    {
        { 1000, 0 },
        { 3900, 2450 },
        { 7000, 5450 },
        { 10300, 8650 },
        { 10300, 10300 },
    },
};
