#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_00[0x18];
    void *vramTiles;
    void *workTiles;
} GaugeContext;

extern GaugeContext *gFieldHudGaugeState;

extern const u8 gGaugeFilledRow[];
extern const u8 gGaugeEmptyRow[];
extern const u8 gGaugeTransitionRow1[];
extern const u8 gGaugeTransitionRow2[];

extern void BlitGaugeFillPattern(void *tiles, s32 row, const u8 *pattern);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void DrawGaugeFill(s32 filledRows)
{
    GaugeContext *gauge = gFieldHudGaugeState;
    s32 row;

    for (row = 0; row < filledRows; row++) {
        BlitGaugeFillPattern(gauge->workTiles, row, gGaugeFilledRow);
    }
    BlitGaugeFillPattern(gauge->workTiles, row++, gGaugeTransitionRow1);
    BlitGaugeFillPattern(gauge->workTiles, row++, gGaugeTransitionRow2);
    for (; row <= 50; row++) {
        BlitGaugeFillPattern(gauge->workTiles, row, gGaugeEmptyRow);
    }
    MIi_CpuCopyFast(gauge->workTiles, gauge->vramTiles, 0xe0);
}
