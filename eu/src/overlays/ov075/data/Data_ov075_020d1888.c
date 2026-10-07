#include "nitro/types.h"

#pragma explicit_zero_data on

typedef struct MenuViewportDimensions {
    u16 width;
    u16 height;
    u16 maximum;
    u16 terminator;
} MenuViewportDimensions;

MenuViewportDimensions sMenuViewportDimensions = {
    120, 37, 100, 0,
};
