#include "nitro/types.h"

typedef struct MenuPoint {
    u16 x;
    u16 y;
    u8 pad_04[4];
} MenuPoint;

typedef struct MenuCursor {
    u8 pad_00[6];
    MenuPoint points[3];
    s16 current;
} MenuCursor;

typedef struct CursorPosition {
    u32 x;
    u32 y;
} CursorPosition;

extern MenuCursor *data_ov002_0206c46c;
extern void func_01ff8830(void *dst, int value, u32 size);

void GetMenuCursorPosition_02066bdc(CursorPosition *out)
{
    CursorPosition position;

    func_01ff8830(&position, 0, sizeof(position));
    if (data_ov002_0206c46c != NULL) {
        position.x = data_ov002_0206c46c->points[data_ov002_0206c46c->current].x;
        position.y = data_ov002_0206c46c->points[data_ov002_0206c46c->current].y;
    }
    *out = position;
}
