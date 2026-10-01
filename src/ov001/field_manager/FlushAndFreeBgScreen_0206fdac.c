#include "nitro/types.h"

typedef struct LayerList {
    int layers[3];
} LayerList;

typedef struct BgScreen {
    u8 pad_000[0x448];
    void *bg3Char;
    void *bg2Char;
    void *screenBuffers[3];
    void *palette;
} BgScreen;

extern LayerList data_ov001_0209dbac;
extern int func_ov001_0207123c(void);
extern void func_020033e0(void);
extern int UpdateWidgetLayerDefault_020b9df0(int widgets, int layer);
extern void func_ov027_020b9e00(int widgets, int layer);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void func_02007250(void *dest, u32 srcOffset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FlushAndFreeBgScreen_0206fdac(BgScreen *screen)
{
    int widgets = func_ov001_0207123c();
    LayerList list = data_ov001_0209dbac;
    int *layers = list.layers;
    int i;

    func_020033e0();
    for (i = 0; i < 3; i++) {
        int layer = layers[i];
        func_01ff878c(screen->screenBuffers[i], (void *)UpdateWidgetLayerDefault_020b9df0(widgets, layer), 0x800);
        func_ov027_020b9e00(widgets, layer);
    }
    GX_LoadBG3Char_02007b70(screen->bg3Char, 0, 0x5b00);
    GX_LoadBG2Char_02007a90(screen->bg2Char, 0, 0x1000);
    func_02007250(screen->palette, 0, 0x200);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(screen->palette);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(screen->bg2Char);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(screen->bg3Char);
    screen->palette = NULL;
    screen->bg2Char = NULL;
    screen->bg3Char = NULL;
    for (i = 0; i < 3; i++) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(screen->screenBuffers[i]);
        screen->screenBuffers[i] = NULL;
    }
}
