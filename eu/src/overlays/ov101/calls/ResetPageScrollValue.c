#include "src/overlays/ov101/PageScrollState.h"

void ResetPageScrollValue(int index)
{
    Ov101PageScrollState *state = gListMenuGlobalStorage;
    PageScrollValue *scroll = &state->pageScroll[index];

    scroll->target = 0;
    scroll->current = 0;
}
