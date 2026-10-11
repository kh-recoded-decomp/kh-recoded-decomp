#include "nitro/types.h"

typedef struct DigitPos {
    s32 x;
    s32 y;
} DigitPos;

extern void *FindWidgetById_020b90a4(void *root, int id);
extern DigitPos *func_ov027_020b91a8(void *root, void *widget);
extern int func_0204f0b4(void *recordBase, int kind, int flags);
extern void func_0204f2e4(void *recordBase, int recordIndex);
extern void func_0204f13c(void *recordBase, int recordIndex, DigitPos *position);
extern void func_0204f204(void *recordBase, int recordIndex, int cell);
extern void func_0204f378(void *recordBase, int recordIndex, int visible);

s16 DrawWidgetPlayTime_020be358(void *records, int widgetId, int kind, u32 seconds)
{
    DigitPos pos;
    s16 digit;
    s16 record;
    s16 base;
    int width;

    pos = *func_ov027_020b91a8(records, FindWidgetById_020b90a4(records, widgetId));
    if (seconds > 3599999) {
        seconds = 3599999;
    }
    for (digit = 0; digit < 9; digit++) {
        base = (digit == 1 || digit == 4) ? 6 : 10;
        record = func_0204f0b4(records, kind, 0);
        func_0204f2e4(records, record);
        func_0204f13c(records, record, &pos);
        if (digit == 2 || digit == 5) {
            func_0204f204(records, record, 10);
            func_0204f378(records, record, 1);
        } else {
            func_0204f204(records, record, (u16)(seconds % base));
            func_0204f378(records, record, (digit < 7 || seconds != 0) ? 1 : 0);
            seconds = seconds / base;
        }
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
    return record - 8;
}

