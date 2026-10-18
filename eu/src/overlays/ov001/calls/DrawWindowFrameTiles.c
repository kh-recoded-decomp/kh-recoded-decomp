#pragma opt_propagation on

#include "src/overlays/ov001/WindowTileMap.h"

enum WindowFrameTile {
    FRAME_TOP_LEFT = 2,
    FRAME_TOP = 3,
    FRAME_TOP_RIGHT = 4,
    FRAME_LEFT = 5,
    FRAME_CENTER = 6,
    FRAME_RIGHT = 7,
    FRAME_BOTTOM_LEFT = 8,
    FRAME_BOTTOM = 9,
    FRAME_BOTTOM_RIGHT = 10
};

void DrawWindowFrameTiles(WindowTileMap *map, int x, int y,
                          int width, int height, u16 attributes)
{
    int offset;
    int column;
    int fillTile;
    u16 *top;
    u16 *bottom;

    if (width < 1 || height < 1) {
        return;
    }
    int flags = attributes;
    top = &map->tiles[y * 32];
    top[x] = flags | FRAME_TOP_LEFT;
    top[x + width] = flags | FRAME_TOP_RIGHT;
    bottom = &map->tiles[(y + height) * 32];
    bottom[x] = flags | FRAME_BOTTOM_LEFT;
    bottom[x + width] = flags | FRAME_BOTTOM_RIGHT;

    offset = 1;
    if (width > 1) {
        do {
            top[x + offset] = flags | FRAME_TOP;
            bottom[x + offset] = flags | FRAME_BOTTOM;
            ++offset;
        } while (offset < width);
    }
    offset = 1;
    if (height > 1) {
        do {
            u16 *left = map->tiles + x;
            u16 *right = map->tiles + (x + width);
            left[(y + offset) * 32] = flags | FRAME_LEFT;
            right[(y + offset) * 32] = flags | FRAME_RIGHT;
            ++offset;
        } while (offset < height);
    }
    offset = 1;
    if (height > 1) {
        fillTile = flags | FRAME_CENTER;
        do {
            u16 *startColumn = map->tiles + x;
            column = 1;
            if (width > 1) {
                do {
                    u16 *line = startColumn + (y + offset) * 32;
                    line[column] = fillTile;
                    ++column;
                } while (column < width);
            }
            ++offset;
        } while (offset < height);
    }
}
