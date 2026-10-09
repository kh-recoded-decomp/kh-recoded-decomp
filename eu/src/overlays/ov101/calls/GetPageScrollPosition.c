#include "src/overlays/ov101/PageScrollState.h"

int GetPageScrollPosition(int index)
{
    return data_ov101_020c5920->pageScroll[index].current >> 12;
}
