#include "nitro/types.h"

typedef struct TouchRect {
    u8 width;
    u8 height;
    s8 marginX;
    s8 marginY;
} TouchRect;

const TouchRect sVolumeSliderTouchRect = {
    192, 32, 0, 0,
};
