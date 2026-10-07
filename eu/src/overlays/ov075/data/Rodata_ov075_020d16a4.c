#include "nitro/types.h"

typedef struct FrameRowTiles {
    u16 left;
    u16 middle;
    u16 right;
} FrameRowTiles;

typedef struct FrameTiles {
    FrameRowTiles rows[3];
    u16 padding;
} FrameTiles;

const FrameTiles sFrameTiles = {
    {
        { 0x0001, 0x0002, 0x0401 },
        { 0x0003, 0x0004, 0x0403 },
        { 0x0801, 0x0802, 0x0C01 },
    },
    0,
};
