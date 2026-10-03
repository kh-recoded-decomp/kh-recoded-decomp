#include "nitro/types.h"

typedef struct {
    u8 pad00[0x34];
    BOOL dirty;
    u8 pad38[0x4c];
    u16 layerB[0x600];
    u16 layerA[0x600];
} TileLayers;

typedef struct {
    u16 pad00;
    s16 x;
    s16 y;
    u16 pad06[2];
    s16 width;
    s16 height;
    u16 pad0e;
    int layer;
} TileRect;

extern TileLayers *data_ov045_020c0880;

extern void func_01ff8684(u16 value, void *dst, u32 size);

void ClearTileRect_020c01ac(TileRect *rect)
{
    TileLayers *layers = data_ov045_020c0880;
    u16 *tiles;

    if (rect->layer == 11) {
        tiles = layers->layerB;
    } else if (rect->layer == 10) {
        tiles = layers->layerA;
    } else {
        tiles = NULL;
    }
    if (tiles != NULL) {
        u16 size = rect->width * 2;
        s16 rows;

        tiles = tiles + rect->x + rect->y * 32;
        for (rows = rect->height; rows > 0; rows--) {
            func_01ff8684(0, tiles, size);
            tiles += 32;
        }
        layers->dirty = TRUE;
    }
}
