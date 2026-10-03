#include "nitro/types.h"

typedef struct TileScreen TileScreen;
typedef struct TileWidget TileWidget;

extern int ClipWidgetToScreen_020b99a0(TileScreen *screen, TileWidget *widget, int *xOut, int *yOut, int *widthOut,
                                       int *heightOut);
extern void func_01ff8684(u32 value, void *dst, u32 size);

void ClearWidgetScreenRegion_020b9c50(TileScreen *screen, TileWidget *widget, u16 *buffer)
{
    int x;
    int y;
    int width;
    int height;
    int row;
    int stride;

    if (buffer == NULL) {
        return;
    }
    stride = ClipWidgetToScreen_020b99a0(screen, widget, &x, &y, &width, &height);
    for (row = 0; row < height; row++) {
        func_01ff8684(0, &buffer[stride * (y + row) + x], width * 2);
    }
}

