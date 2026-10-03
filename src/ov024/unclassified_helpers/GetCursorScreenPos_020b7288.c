#include "nitro/types.h"

typedef struct BoardState {
    char pad0000[0x6558];
    s16 originX;
    s16 originY;
} BoardState;

typedef struct BoardCursor {
    char pad00[0x37];
    s8 directions[0x55 - 0x37];
    s8 index;
} BoardCursor;

typedef struct BoardGlobals {
    BoardState *state;
    int unk04;
    BoardCursor *cursor;
} BoardGlobals;

typedef struct CellOffset {
    int x;
    int y;
} CellOffset;

extern BoardGlobals data_ov024_020b7520;
extern CellOffset data_ov024_020b7384[];
extern void func_ov024_020b7228(int *pos, int *offset, int direction);

void GetCursorScreenPos_020b7288(int *pos, int *offset)
{
    pos[0] = (data_ov024_020b7520.state->originX + data_ov024_020b7384[data_ov024_020b7520.cursor->index].x) << 12;
    pos[1] = (data_ov024_020b7520.state->originY + data_ov024_020b7384[data_ov024_020b7520.cursor->index].y) << 12;
    func_ov024_020b7228(pos, offset, data_ov024_020b7520.cursor->directions[data_ov024_020b7520.cursor->index]);
}
