#include "nitro/types.h"

typedef struct TileRect {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} TileRect;

typedef struct TileObject {
    u8 reserved00[0x24];
    u8 *tiles;
} TileObject;

typedef struct TileObjectContext {
    u8 reserved00[0x20];
    TileObject *object;
} TileObjectContext;

/* Copies 4bpp tiles from a 32-column map into an object's linear buffer. */
void ExtractTileRect(TileObjectContext *context, const TileRect *rect,
                     const u8 *tileData, const u16 *mapData)
{
    int x = rect->x;
    u8 *destination = context->object->tiles;
    int y = rect->y;
    int width = rect->width;
    int height = rect->height;
    int row;
    for (row = 0; row < height; ++row) {
        int column;
        for (column = 0; column < width; ++column) {
            u16 tile = mapData[(y + row) * 32 + x + column] & 0x3ff;
            const u8 *source = tileData + tile * 32;
            int byte;
            for (byte = 0; byte < 32; ++byte) {
                *destination++ = source[byte];
            }
        }
    }
}
