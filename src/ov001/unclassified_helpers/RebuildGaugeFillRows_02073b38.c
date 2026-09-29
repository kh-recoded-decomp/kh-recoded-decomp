#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_00[0x4c];
    s32 unitCost;
    u8 pad_50[0xc6 - 0x50];
    u16 totalUnits;
} GaugeContext;

extern GaugeContext *data_ov001_020a04ac;

extern s32 func_02023dbc(s32 numerator, s32 denominator);
extern void func_ov001_020738d4(s32 row, BOOL filled, BOOL isLast);

void RebuildGaugeFillRows_02073b38(s32 filledUnits)
{
    GaugeContext *gauge = data_ov001_020a04ac;
    s32 quotient = func_02023dbc(gauge->totalUnits * 0x30, gauge->unitCost * 200);
    s32 totalRows;
    s32 filledRows;
    s32 row;

    if (quotient > 0) {
        totalRows = func_02023dbc(quotient - 1, 0x30);
    } else {
        totalRows = 0;
    }
    if (filledUnits > 0) {
        filledRows = func_02023dbc(filledUnits - 1, 0x30);
    } else {
        filledRows = 0;
    }
    if (totalRows <= 0) {
        return;
    }
    for (row = 0; row < totalRows - 1; row++) {
        func_ov001_020738d4(row, row < filledRows, FALSE);
    }
    func_ov001_020738d4(totalRows - 1, totalRows - 1 < filledRows, TRUE);
}
