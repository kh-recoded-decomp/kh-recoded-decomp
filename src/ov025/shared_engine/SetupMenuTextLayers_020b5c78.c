#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 tileOffset;
    u16 unk_a;
    u16 unk_c;
    u16 unk_e;
} TextFrame;

typedef struct WidgetSetup {
    u32 values[5];
} WidgetSetup;

extern u32 g_uiContext_020b7760;
extern WidgetSetup data_ov025_020b76c0;
extern TextFrame data_ov025_020b76b0;

extern void func_ov027_020b7d58(u32 container, WidgetSetup *setup);
extern void *func_ov001_0207123c(void);
extern void ClearTileTableRowAndMarkDirty_020b9d18(void *table, int id);
extern u16 *UpdateWidgetLayerDefault_020b9df0(void *owner, int layerId);
extern void *GetFieldFont3_020711e0(void);
extern void *GetFieldFont2_020711d4(void);
extern BOOL InitTextLayerAtFromEnd_020014d0(void *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern int CountActiveSlots_020b74d8(u32 entity);
extern void DrawRemainingCountText_020b5858(u32 screen, int count);
extern u32 func_ov001_02073684(void);
extern void func_0200160c(void *context, u32 x, u32 y, u32 color, u32 flags, u32 text, void *font, int maxWidth);
extern void Text_UploadTileBuffer_02001520(void *context);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern void MarkTileTableRowDirty_020b9e00(void *table, int id);
extern void GXS_LoadBG0Scr_020075c0(const void *src, u32 offset, u32 size);
extern void ResolveEntryStoreWord_020b9088(u32 container, int id, void *handler);
extern void HandleDefaultMenuAction_020b5a94(void);
extern u32 RefreshTagCallbacksAndSchedule_020b5e24(void);

void *SetupMenuTextLayers_020b5c78(void)
{
    u32 menu = g_uiContext_020b7760;
    WidgetSetup setup = data_ov025_020b76c0;
    TextFrame frame;
    void *tileTable;
    u16 *screenBase;

    func_ov027_020b7d58(menu, &setup);
    frame = data_ov025_020b76b0;
    tileTable = func_ov001_0207123c();
    ClearTileTableRowAndMarkDirty_020b9d18(tileTable, 0x18);
    screenBase = UpdateWidgetLayerDefault_020b9df0(tileTable, 0x18);
    InitTextLayerAtFromEnd_020014d0((void *)(menu + 0x6634), 4, screenBase, GetFieldFont3_020711e0(), &frame);
    DrawRemainingCountText_020b5858(menu, CountActiveSlots_020b74d8(menu + 0x64f4));

    frame.x = 2;
    frame.y = 0;
    frame.width = 0xb;
    frame.height = 2;
    frame.tileOffset = 0x1a0;
    InitTextLayerAtFromEnd_020014d0((void *)(menu + 0x6668), 4, screenBase, GetFieldFont3_020711e0(), &frame);
    func_0200160c((void *)(menu + 0x6668), 1, 3, 2, 0x209, func_ov001_02073684(), GetFieldFont2_020711d4(), 0x50);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        FlushBufferAndRunCallback_0200153c((void *)(menu + 0x6668));
    } else {
        Text_UploadTileBuffer_02001520((void *)(menu + 0x6668));
    }

    frame.x = 0;
    frame.y = 0x15;
    frame.width = 0x1d;
    frame.height = 3;
    frame.tileOffset += 0x16;
    InitTextLayerAtFromEnd_020014d0((void *)(menu + 0x669c), 4, screenBase, GetFieldFont3_020711e0(), &frame);
    func_0200160c((void *)(menu + 0x669c), 4, 0, 2, 0x209, func_ov001_02073684(), GetFieldFont2_020711d4(), 0xe4);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        FlushBufferAndRunCallback_0200153c((void *)(menu + 0x669c));
    } else {
        Text_UploadTileBuffer_02001520((void *)(menu + 0x669c));
    }

    MarkTileTableRowDirty_020b9e00(tileTable, 0x18);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        GXS_LoadBG0Scr_020075c0(screenBase, 0, 0x800);
    }
    *(int *)(menu + 0x66d8) = 1;
    ResolveEntryStoreWord_020b9088(menu + 0x4c, 3, HandleDefaultMenuAction_020b5a94);
    return RefreshTagCallbacksAndSchedule_020b5e24;
}
