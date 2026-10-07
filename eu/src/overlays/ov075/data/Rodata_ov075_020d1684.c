#include "nitro/types.h"

typedef struct LevelThresholds {
    s32 values[4];
} LevelThresholds;

const LevelThresholds sPartyLevelThresholds = {
    { 1000, 3900, 7000, 10300 },
};
