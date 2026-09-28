#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextWindow;

typedef struct {
    u8 pad_00[0x10];
    TextWindow *windows;
} TextWindowSet;

extern void FillBackgroundLayerRect_02001a60(void *window, u16 *dst, int x, int y, u8 palette);

void FillTextWindowBackground_02079770(TextWindowSet *set, u16 *dst, int unused, int windowIndex, int x, int y)
{
    FillBackgroundLayerRect_02001a60(&set->windows[windowIndex], dst, (u16)x, (u16)y, 0xf);
}
