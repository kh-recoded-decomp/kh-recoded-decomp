#include "src/overlays/ov101/PageScrollState.h"

int GetPageScrollPosition(int index)
{
    return gListMenuGlobalStorage->pageScroll[index].current >> 12;
}
