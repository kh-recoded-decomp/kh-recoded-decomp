#include "src/overlays/ov101/PageScrollState.h"

BOOL IsPageScrollSettled(int index)
{
    PageScrollValue *scrolls = data_ov101_020c5920->pageScroll;
    PageScrollValue *scroll = &scrolls[index];
    fx32 distance = scroll->target - scroll->current;

    if (distance < 0) {
        distance = (fx32)(((s64)distance * -1 + 0x800) >> 12);
    }
    return (distance >> 12) < 1;
}
