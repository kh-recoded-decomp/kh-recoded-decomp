#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x14];
    void *buffer;
    u8 pad_18[0x34];
    s32 useWhiteClearColor;
} ScreenLayer;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void *G2_GetBG1CharPtr_020070cc(void);
extern void *G2S_GetBG0ScrPtr_02006e14(void);
extern void *G2S_GetBG0CharPtr_020070ac(void);
extern void MIi_CpuClearFast_01ff8740(u32 value, void *dest, u32 size);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void func_020072b4(const void *src, u32 offset, u32 size);
extern void G3X_SetClearColor_02006c08(u32 color, u32 alpha, u32 depth, u32 polygonId, BOOL fog);

void ClearScreenLayerGraphics_020bbb64(ScreenLayer *layer, int screen)
{
    u16 backdropColor = 0;

    if (layer->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(layer->buffer);
        layer->buffer = NULL;
    }
    if (screen == 0) {
        MIi_CpuClearFast_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x800);
        MIi_CpuClearFast_01ff8740(0, G2_GetBG1CharPtr_020070cc(), 0x20000);
        func_02007250(&backdropColor, 0, sizeof(backdropColor));
        if (layer->useWhiteClearColor != 0) {
            G3X_SetClearColor_02006c08(0x7ffe, 0x1f, 0x7fff, 0x3f, FALSE);
            return;
        }
        G3X_SetClearColor_02006c08(0, 0, 0x7fff, 0x3f, FALSE);
        return;
    }
    MIi_CpuClearFast_01ff8740(0, G2S_GetBG0ScrPtr_02006e14(), 0x800);
    MIi_CpuClearFast_01ff8740(0, G2S_GetBG0CharPtr_020070ac(), 0x20000);
    func_020072b4(&backdropColor, 0, sizeof(backdropColor));
}
