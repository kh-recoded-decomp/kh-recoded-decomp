#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} DigitPos;

extern void func_0204f378(void *cells, int index, int value);
extern void func_0204f204(void *cells, int index, int value);
extern void func_0204f13c(void *cells, int index, DigitPos *pos);

void SetDigitDisplay_020be2c8(void *cells, int first, int value, DigitPos *origin)
{
    DigitPos pos;
    BOOL visible;
    s16 digit;
    s16 index;

    if (origin != 0) {
        pos = *origin;
    }
    digit = 0;
    index = first;
    do {
        if (value >= 0 && (digit == 0 || value != 0)) {
            visible = TRUE;
        } else {
            visible = FALSE;
        }
        func_0204f378(cells, index, visible);
        if (visible) {
            func_0204f204(cells, index, (u16)(value % 10));
        }
        if (origin != 0) {
            func_0204f13c(cells, index, &pos);
            pos.x -= 0x7000;
        }
        value /= 10;
        digit++;
        index++;
    } while (digit < 6);
}
