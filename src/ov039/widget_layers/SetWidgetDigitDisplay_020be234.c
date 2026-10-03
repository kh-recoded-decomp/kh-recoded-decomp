#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} DigitPos;

extern void *FindWidgetById_020b90a4(void *root, int id);
extern DigitPos *func_ov027_020b91a8(void *root, void *widget);
extern int PXI_Init_0204f0b4(void *cells, int key, int flags);
extern void func_0204f2e4(void *cells, int index);
extern void func_0204f204(void *cells, int index, int value);
extern void func_0204f13c(void *cells, int index, DigitPos *pos);
extern void func_0204f378(void *cells, int index, int value);

s16 SetWidgetDigitDisplay_020be234(void *cells, int widgetId, int key, u32 value)
{
    DigitPos pos = *func_ov027_020b91a8(cells, FindWidgetById_020b90a4(cells, widgetId));
    s16 digit = 0;
    s16 index;

    do {
        index = PXI_Init_0204f0b4(cells, key, 0);
        func_0204f2e4(cells, index);
        func_0204f204(cells, index, (u16)(value % 10));
        func_0204f13c(cells, index, &pos);
        func_0204f378(cells, index, digit == 0 || value != 0);
        pos.x -= 0x7000;
        value /= 10;
        digit++;
    } while (digit < 6);
    return index - 5;
}
