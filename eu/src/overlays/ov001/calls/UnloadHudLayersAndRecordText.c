/* Undoes LoadHudLayersAndRecordText: copies the three saved widget layers back into their tile
 * tables, frees the copies and the record text, and redraws the field menu and text window. */
#include "nitro/types.h"

typedef struct LayerIdTable {
    int ids[3];
} LayerIdTable;

typedef struct EntrySummary EntrySummary;

typedef struct HudContext {
    u8 pad_000[0x2e4];
    s32 unk_2E4;
    s32 unk_2E8;
    u8 pad_2ec[0x2f4 - 0x2ec];
    u8 unk_2F4[0x450 - 0x2f4];
    void *layerBuffers[3];
    u8 pad_45c[0x480 - 0x45c];
    u32 unk_480_0 : 8;
    u32 layersRequested : 1;
    u32 layersLoaded : 1;
    u32 unk_480_10 : 10;
    u32 unk_480_20 : 1;
    u32 unk_480_21 : 11;
    u8 pad_484[0x51c - 0x484];
    u8 textWindow[0x6e4 - 0x51c];
    EntrySummary *entrySummaries;
    u16 *recordText;
} HudContext;

typedef struct HudGlobals {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;
extern const LayerIdTable gFieldHudRestoreLayerIds;

extern void *func_ov001_0207123c(void);
extern void func_ov001_0206fa2c(HudContext *context);
extern void *UpdateWidgetLayerDefault_020b9e10(void *widgets, int layer);
extern void MarkTileTableRowDirty(void *widgets, int layer);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);
extern void ShutDownStageCaption(void *object);
extern void func_ov035_020bc3d8(void);
extern void func_ov001_02078180(void);
extern void CallVirtualHandlerSlot1(void *object, int arg);
extern void Text_UploadTileBuffer(void *window);

void UnloadHudLayersAndRecordText(void)
{
    HudContext *context = data_ov001_020a04c4.context;
    void *widgets = func_ov001_0207123c();
    LayerIdTable layers = gFieldHudRestoreLayerIds;
    int i;
    int layer;
    void *tile;

    if (!context->layersRequested || !context->layersLoaded) {
        return;
    }
    func_ov001_0206fa2c(context);
    context->layersLoaded = 0;
    context->unk_480_20 = 0;
    context->unk_2E4 = 0;
    context->unk_2E8 = 0;
    for (i = 0; i < 3; i++) {
        layer = layers.ids[i];
        tile = UpdateWidgetLayerDefault_020b9e10(widgets, layer);
        MIi_CpuCopyFast(context->layerBuffers[i], tile, 0x800);
        MarkTileTableRowDirty(widgets, layer);
        NNSi_FndFreeFromDefaultHeap(context->layerBuffers[i]);
        context->layerBuffers[i] = NULL;
    }
    ShutDownStageCaption(context->unk_2F4);
    NNSi_FndFreeFromDefaultHeap(context->entrySummaries);
    context->entrySummaries = NULL;
    NNSi_FndFreeFromDefaultHeap(context->recordText);
    context->recordText = NULL;
    func_ov035_020bc3d8();
    func_ov001_02078180();
    CallVirtualHandlerSlot1(context->textWindow, 0);
    Text_UploadTileBuffer(context->textWindow);
}
