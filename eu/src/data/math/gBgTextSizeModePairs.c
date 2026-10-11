#include "nitro/types.h"

typedef struct BgSizeModePair {
    s16 width;
    s16 height;
    s16 mode;
} BgSizeModePair;

const BgSizeModePair gBgTextSizeModePairs[4] = {
    { 256, 256, 0 },
    { 256, 512, 2 },
    { 512, 256, 1 },
    { 512, 512, 3 },
};
