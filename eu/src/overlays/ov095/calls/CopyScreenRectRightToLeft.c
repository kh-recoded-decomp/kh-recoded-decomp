#pragma opt_propagation off

#include "nitro/types.h"

typedef struct ScreenData {
    u16 pixelWidth;
    u16 pixelHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 byteSize;
    u16 tiles[1];
} ScreenData;

typedef char ScreenTilesOffsetCheck[(u32)&((ScreenData *)0)->tiles == 0x0c ? 1 : -1];

extern int GetTiledPixelIndex(int x, int y, int width, int height);

/* The original routine copies within screen->tiles and ignores the first argument.
 * Coordinates and rectangle dimensions are in tiles, not pixels. */
void CopyScreenRectRightToLeft(void *unusedDestination, ScreenData *screen,
                             int sourceX, int sourceY, int destinationX, int destinationY,
                             int destinationWidth, int destinationHeight, int width, int height)
{
#pragma unused(unusedDestination)
    int sourceByteOffset;
    u16 *tiles;
    int x;
    int destinationColumn;
    int destinationRow = destinationY;
    const int sourceLimit = sourceX + width;
    const int destinationLimit = destinationX + width;
    const int sourceWidth = (u32)screen->pixelWidth >> 3;
    const int sourceHeight = (u32)screen->pixelHeight >> 3;
    tiles = screen->tiles;
    int endY = sourceY + height;

    /* Keep the empty-row guard separate from the original loop preheader. */
    if (sourceY < endY) {
        for (; sourceY < endY; ++sourceY, ++destinationRow) {
            x = sourceLimit - 1;
            destinationColumn = destinationLimit - 1;
            for (; x >= sourceX; --x, --destinationColumn) {
                sourceByteOffset = 2 * GetTiledPixelIndex(x, sourceY, sourceWidth, sourceHeight);
                int destinationByteOffset = 2 * GetTiledPixelIndex(destinationColumn, destinationRow,
                                                                  destinationWidth, destinationHeight);
                *(u16 *)((u8 *)tiles + destinationByteOffset) = *(u16 *)((u8 *)tiles + sourceByteOffset);
            }
        }
    }
}
