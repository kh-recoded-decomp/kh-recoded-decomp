#include "nitro/types.h"

typedef struct HudContext {
    u8 pad_000[0x448];
    void *bgVramBackup;
    void *bg2CharBackup;
    void *widgetLayerBackups[3];
    void *paletteBackup;
} HudContext;

typedef struct WidgetLayerIds {
    int ids[3];
} WidgetLayerIds;

extern const WidgetLayerIds data_ov001_0209dbb8;
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void *G2_GetBG2CharPtr_02007120(void);
extern void *func_ov001_0207123c(void);
extern void *UpdateWidgetLayerDefault_020b9df0(void *widgets, int layer);

static inline BOOL DisableIrq(void)
{
    u16 previous = *(vu16 *)0x04000208;
    *(vu16 *)0x04000208 = 0;
    return previous;
}

static inline BOOL EnableIrq(void)
{
    u16 previous = *(vu16 *)0x04000208;
    *(vu16 *)0x04000208 = 1;
    return previous;
}

void BackupSceneVram_0206fcc8(HudContext *context)
{
    WidgetLayerIds layers = data_ov001_0209dbb8;
    BOOL irqEnabled;
    void *buffer;
    void *layer;
    int i;

    irqEnabled = DisableIrq();
    context->bgVramBackup = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x5b00, -0x20);
    func_01ff878c((void *)0x06000000, context->bgVramBackup, 0x5b00);
    buffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x1000, -0x20);
    context->bg2CharBackup = buffer;
    func_01ff878c(G2_GetBG2CharPtr_02007120(), buffer, 0x1000);
    for (i = 0; i < 3; i++) {
        context->widgetLayerBackups[i] = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x800, -0x20);
        buffer = context->widgetLayerBackups[i];
        layer = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), layers.ids[i]);
        func_01ff878c(layer, buffer, 0x800);
    }
    context->paletteBackup = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x200, -0x20);
    func_01ff878c((void *)0x05000000, context->paletteBackup, 0x200);
    if (irqEnabled) {
        EnableIrq();
    }
}
