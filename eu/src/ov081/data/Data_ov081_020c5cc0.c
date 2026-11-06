#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv081Screen(void);
extern void ScrollListBackward(void);
extern void ScrollListForward(void);
extern void DrawTutorialPageIndicatorThunk(void);
extern void DestroyOv081Screen(void);
extern void CloseOverlay081Menu(void);

void *gTutorialMenuDescriptor[17] = {
    (void *)InitOv081Screen,
    (void *)DestroyOv081Screen,
    (void *)DrawTutorialPageIndicatorThunk,
    (void *)0x0000000B,
    (void *)0x000063E8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)CloseOverlay081Menu,
    NULL,
    NULL,
    (void *)ScrollListBackward,
    (void *)ScrollListForward,
    NULL,
    (void *)CloseOverlay081Menu,
};
