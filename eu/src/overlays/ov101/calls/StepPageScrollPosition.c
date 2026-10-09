#include "src/overlays/ov101/PageScrollState.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

static inline fx32 FxMulRounded(fx32 left, fx32 right)
{
    return (fx32)(((s64)left * right + 0x800) >> 12);
}

void StepPageScrollPosition(int index)
{
    Ov101PageScrollState *state = data_ov101_020c5920;
    PageScrollValue *scroll = &state->pageScroll[index];
    fx32 scale = FX_Div(123, 614);

    scroll->current += FxMulRounded(scroll->target - scroll->current, scale);
}
