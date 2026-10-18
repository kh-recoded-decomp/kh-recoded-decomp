#ifndef KH_RECODED_OV001_WINDOW_TILE_MAP_H
#define KH_RECODED_OV001_WINDOW_TILE_MAP_H

#include "nitro/types.h"

typedef struct WindowTileMap {
    u16 tiles[32 * 32];
} WindowTileMap;

/* Width and height are offsets to the far border, not counts including it. */
void DrawWindowFrameTiles(WindowTileMap *map, int x, int y,
                          int width, int height, u16 attributes);

#endif
