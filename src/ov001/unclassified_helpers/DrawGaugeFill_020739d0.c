#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_00[0x18];
    void *vramTiles;
    void *workTiles;
} GaugeContext;

extern GaugeContext *data_ov001_020a04ac;

extern const u8 data_ov001_0209ddc4[];
extern const u8 data_ov001_0209ddca[];
extern const u8 data_ov001_0209dde6[];
extern const u8 data_ov001_0209ddec[];

extern void func_ov001_020738b8(void *tiles, s32 row, const u8 *pattern);
extern void func_01ff878c(const void *src, void *dst, u32 size);

void DrawGaugeFill_020739d0(s32 filledRows)
{
    GaugeContext *gauge = data_ov001_020a04ac;
    s32 row;

    for (row = 0; row < filledRows; row++) {
        func_ov001_020738b8(gauge->workTiles, row, data_ov001_0209ddc4);
    }
    func_ov001_020738b8(gauge->workTiles, row++, data_ov001_0209dde6);
    func_ov001_020738b8(gauge->workTiles, row++, data_ov001_0209ddec);
    for (; row <= 50; row++) {
        func_ov001_020738b8(gauge->workTiles, row, data_ov001_0209ddca);
    }
    func_01ff878c(gauge->workTiles, gauge->vramTiles, 0xe0);
}
