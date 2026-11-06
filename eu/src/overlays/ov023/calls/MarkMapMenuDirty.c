#include "nitro/types.h"

typedef struct MapMenuState {
    u8 pad_00[0x2c];
    BOOL dirty;
} MapMenuState;

extern MapMenuState *gMapMenuWork;

void MarkMapMenuDirty(void)
{
    gMapMenuWork->dirty = TRUE;
}
