#include "nitro/types.h"

typedef struct TouchRect {
    u8 width;
    u8 height;
    s8 marginX;
    s8 marginY;
} TouchRect;

typedef struct FlagGridTouchConfig {
    TouchRect bounds;
    u32 packedActiveBounds;
} FlagGridTouchConfig;

const FlagGridTouchConfig sFlagGridTouchConfig = {
    { 96, 96, 0, 0 },
    0xEF385050,
};
