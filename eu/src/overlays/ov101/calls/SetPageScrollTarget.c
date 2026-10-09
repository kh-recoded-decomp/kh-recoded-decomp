#include "src/overlays/ov101/PageScrollState.h"

void SetPageScrollTarget(int index, int value)
{
    Ov101PageScrollState *state = data_ov101_020c5920;
    PageScrollValue *scroll = state->pageScroll;
    float scaled;

    if ((float)value > 0.0f) {
        scaled = (float)value * 4096.0f + 0.5f;
    } else {
        scaled = (float)value * 4096.0f - 0.5f;
    }
    scroll[index].target = (s32)scaled;
}
