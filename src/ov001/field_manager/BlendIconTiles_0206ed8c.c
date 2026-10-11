#include "nitro/types.h"

typedef struct IconTileContext {
    u8 pad_000[0x460];
    u8 *tilesLow;
    u8 *tilesHigh;
    u8 *tilesMid;
    u8 *workTiles;
    u8 pad_470[0x10];
    u32 pad_480_0 : 15;
    u32 blendLocked : 1;
} IconTileContext;

typedef struct IconTileGlobals {
    u32 unk_00;
    IconTileContext *context;
} IconTileGlobals;

typedef struct ThresholdTable {
    u32 values[5];
} ThresholdTable;

extern IconTileGlobals data_ov001_020a04a4;
extern ThresholdTable data_ov001_0209dcbc;

extern BOOL func_ov001_020728e4(void);
extern int func_ov001_0207b590(void);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_020033e0(void);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);

void BlendIconTiles_0206ed8c(u16 value)
{
    int tailSize;
    u8 *from;
    int low;
    int high;
    int row;
    int index;
    int offset;
    int step;
    int rightStart;
    u8 *to;
    int frame;
    IconTileContext *context;
    int col;
    int half;
    ThresholdTable table;
    u32 target;
    int tail;
    u8 *dst;
    int leftCount;
    int head;
    u8 *toTile;
    u8 *fromTile;

    context = data_ov001_020a04a4.context;
    table = data_ov001_0209dcbc;
    if (context->blendLocked == 1) {
        return;
    }

    if (func_ov001_020728e4()) {
        target = 0xce4;
        low = 0;
        high = 0xce4;
    } else {
        target = table.values[func_ov001_0207b590()];
        if (value >= 7000) {
            low = 7000;
            high = 0x283c;
        } else if (value >= 0xf3c) {
            low = 0xf3c;
            high = 7000;
        } else if (value >= 1000) {
            low = 1000;
            high = 0xf3c;
        } else {
            low = 0;
            high = 1000;
        }
    }

    offset = value - low;
    high -= low;
    half = high / 2;
    if (value == target) {
        func_01ff878c(context->tilesHigh, context->workTiles, 0x80);
    } else if (low != 0 && offset == half) {
        func_01ff878c(context->tilesMid, context->workTiles, 0x80);
    } else {
        if (low == 0) {
            from = context->tilesLow;
            to = context->tilesHigh;
            frame = offset * 30 / high;
        } else {
            if (offset < half) {
                from = context->tilesLow;
                to = context->tilesMid;
            } else {
                from = context->tilesMid;
                to = context->tilesHigh;
            }
            frame = offset % half * 30 / half;
        }

        if (frame == 0) {
            func_01ff878c(from, context->workTiles, 0x80);
        } else if (frame == 30) {
            func_01ff878c(to, context->workTiles, 0x80);
        } else {
            head = (frame + 1) / 8 * 32;
            func_01ff878c(to, context->workTiles, head);
            tail = (frame + 8) / 8 * 32;
            tailSize = 0x80 - tail;
            if (tailSize > 0) {
                func_01ff878c(from + tail, context->workTiles + tail, tailSize);
            }
            step = (frame + 1) % 8;
            dst = context->workTiles + head;
            row = 0;
            leftCount = step / 2;
            toTile = to + head;
            fromTile = from + head;
            rightStart = (step + 1) / 2;
            for (; row < 8; row++) {
                for (col = 0; col < leftCount; col++) {
                    index = col + row * 4;
                    dst[index] = toTile[index];
                }
                for (col = rightStart; col < 4; col++) {
                    index = col + row * 4;
                    dst[index] = fromTile[index];
                }
            }
            if (step % 2 == 1) {
                for (row = 0; row < 8; row++) {
                    index = leftCount + row * 4;
                    dst[index] = (toTile[index] & 0xf) | (fromTile[index] & 0xf0);
                }
            }
        }
    }
    func_020033e0();
    GX_LoadBG3Char_02007b70(context->workTiles, 0x5b80, 0x80);
}
