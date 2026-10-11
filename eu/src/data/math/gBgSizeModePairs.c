#include "nitro/types.h"

typedef struct BgSizeModePair {
    s16 width;
    s16 height;
    s16 mode;
} BgSizeModePair;

/* Four dimension pairs accepted by LookupPairValue. */
const BgSizeModePair gBgSizeModePairs[4] = {
    { 128, 128, 0 },
    { 256, 256, 1 },
    { 512, 512, 2 },
    { 1024, 1024, 3 },
};
