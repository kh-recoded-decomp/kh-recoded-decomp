#include "nitro/types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern int CopyRecentTouchPoints_0202b618(TouchSample *table);

BOOL HasRecentTouchPoints_020613f8(void)
{
    TouchSample points[4];

    return CopyRecentTouchPoints_0202b618(points) > 0;
}
