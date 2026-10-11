#include "nitro/types.h"

typedef struct TileMapHeader {
    u16 pixelWidth;
    u8 pad_02[0xA];
    u16 tiles[1];
} TileMapHeader;

typedef struct TileSource {
    u8 pad_00[8];
    TileMapHeader *map;
} TileSource;

typedef struct TileRegion {
    u8 pad_00[6];
    u16 x;
    u16 y;
    s16 width;
    s16 height;
    u8 pad_0E[0xA];
    TileSource *source;
} TileRegion;

void StampTileRegionPalette_020b8284(void *owner, const TileRegion *region, int palette)
{
    TileMapHeader *map;
    u16 *tile;
    u16 paletteBits;
    int row;
    int column;

    paletteBits = (u16)((u32)palette << 12);
    for (row = 0; row < region->height; row++) {
        map = region->source->map;
        tile = map->tiles + (region->x + map->pixelWidth * (region->y + row) / 8);
        for (column = 0; column < region->width; column++) {
            *tile = (u16)(paletteBits | (*tile & 0xFFF));
            tile++;
        }
    }
}



