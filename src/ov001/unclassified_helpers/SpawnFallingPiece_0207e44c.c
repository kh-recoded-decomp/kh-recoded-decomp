#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 values[4];
} PieceSizeTable;

typedef struct {
    s32 isVisible;
    s32 isMirrored;
    fx32 height;
    void *sprite;
    u16 size;
} FallingPiece;

typedef struct {
    s32 mode;
    void *sprites[4];
    u8 pad_14[0xA8 - 0x14];
    u16 lastIndex;
} FallingContext;

extern PieceSizeTable data_ov001_0209e018;
extern s32 func_0202a9d0(s32 range);

void SpawnFallingPiece_0207e44c(FallingContext *context, FallingPiece *piece)
{
    PieceSizeTable sizes = data_ov001_0209e018;
    s32 index;

    piece->height = 0xD0000;
    piece->isVisible = 1;
    piece->isMirrored = func_0202a9d0(2) == 1;
    if (context->lastIndex == 0xFFFF) {
        index = func_0202a9d0(4);
    } else if (func_0202a9d0(3) == 0) {
        index = context->lastIndex;
    } else {
        index = func_0202a9d0(4);
    }
    piece->sprite = context->sprites[index];
    piece->size = sizes.values[index];
    context->lastIndex = index;
}
