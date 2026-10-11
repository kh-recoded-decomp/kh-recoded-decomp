#ifndef RECODED_MENU_GAUGE_TABLES_H
#define RECODED_MENU_GAUGE_TABLES_H

#include "nitro/types.h"

typedef struct {
    u32 values[4];
} LevelTable4;

typedef struct {
    u32 values[5];
} LevelTable5;

typedef struct LevelThresholdTable {
    s32 values[5];
} LevelThresholdTable;

extern const LevelTable4 gMenuGaugeLevelFileIds;
extern const LevelTable4 gMenuGaugeLevelMidpoints;
extern const LevelTable5 gMenuGaugeCapacityByPartySize;
extern const LevelThresholdTable gMenuGaugeBlendThresholds;
extern const LevelThresholdTable gMenuGaugePointThresholds;

#endif
