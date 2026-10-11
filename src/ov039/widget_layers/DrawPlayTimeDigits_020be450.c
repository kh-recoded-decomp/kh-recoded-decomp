#include "nitro/types.h"

typedef struct DigitPos {
    s32 x;
    s32 y;
} DigitPos;

extern void func_0204f13c(void *recordBase, int recordIndex, DigitPos *position);
extern void func_0204f204(void *recordBase, int recordIndex, int cell);
extern void func_0204f378(void *recordBase, int recordIndex, int visible);

void DrawPlayTimeDigits_020be450(void *records, int firstRecord, int seconds, DigitPos *origin)
{
    DigitPos pos;
    s16 digit;
    s16 record;
    s16 base;
    int visible;
    int width;

    if (origin != NULL) {
        pos = *origin;
    }
    if (seconds > 3599999) {
        seconds = 3599999;
    }
    for (digit = 0, record = firstRecord; digit < 9; digit++, record++) {
        if (seconds >= 0 && (digit < 7 || seconds != 0)) {
            visible = TRUE;
        } else {
            visible = FALSE;
        }
        func_0204f378(records, record, visible);
        if (visible) {
            if (digit != 2 && digit != 5) {
                base = (digit == 1 || digit == 4) ? 6 : 10;
                func_0204f204(records, record, (u16)(seconds % base));
                seconds = seconds / base;
            }
            if (origin != NULL) {
                func_0204f13c(records, record, &pos);
                switch (digit) {
                case 1:
                case 4:
                    width = 5 << 12;
                    break;
                case 2:
                case 5:
                    width = 6 << 12;
                    break;
                default:
                    width = 7 << 12;
                    break;
                }
                pos.x -= width;
            }
        }
    }
}


