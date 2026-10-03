#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)

typedef struct CharResource {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharResource;

typedef struct PaletteResource {
    u8 pad_00[0xc];
    u8 *data;
} PaletteResource;

typedef struct StatusPanel {
    u8 pad_000[0x148];
    u8 uploads[0x15c - 0x148];
    BOOL uploadImmediate;
    u8 pad_160[0x168 - 0x160];
    BOOL needsRedraw;
    u8 pad_16c[0x174 - 0x16c];
    BOOL restoreLayers;
    u8 pad_178[0x180 - 0x178];
    CharResource *bgChar;
    u8 pad_184[0x194 - 0x184];
    PaletteResource *bgPalette;
    u8 titleLayer[0x1cc - 0x198];
    u8 textLayer[1];
} StatusPanel;

extern StatusPanel *data_ov073_020c4240;

extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char_02007be0(const void *src, u32 offset, u32 size);
extern void *UpdateScreenWidgetLayer_020bc1e4(int widget);
extern void GXS_LoadBG0Scr_020075c0(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr_020076a0(const void *src, u32 offset, u32 size);
extern void MarkTileTableRowDirty_020b9e00(void *table, int id);
extern void func_ov027_020b9e60(void *uploads);
extern void FlushBufferAndRunCallback_0200153c(void *context);

int RestoreStatusSubScreen_020c1248(void)
{
    REG_DB_BG0CNT = (REG_DB_BG0CNT & 0x43) | 0x0a00;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & 0x43) | 0x0b04;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & 0x43) | 0x4c00;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0x4e04;
    GXS_LoadBGPltt_020072b4(data_ov073_020c4240->bgPalette->data, 0, 0xa0);
    GXS_LoadBGPltt_020072b4(data_ov073_020c4240->bgPalette->data + 0x100, 0x100, 0x100);
    GXS_LoadBG3Char_02007be0(data_ov073_020c4240->bgChar->data, 0, data_ov073_020c4240->bgChar->size);
    GXS_LoadBG0Scr_020075c0(UpdateScreenWidgetLayer_020bc1e4(0x18), 0, 0x800);
    GXS_LoadBG1Scr_020076a0(UpdateScreenWidgetLayer_020bc1e4(0x19), 0, 0x800);
    MarkTileTableRowDirty_020b9e00(data_ov073_020c4240->uploads, 0x1a);
    MarkTileTableRowDirty_020b9e00(data_ov073_020c4240->uploads, 0x1b);
    data_ov073_020c4240->uploadImmediate = TRUE;
    func_ov027_020b9e60(data_ov073_020c4240->uploads);
    data_ov073_020c4240->uploadImmediate = FALSE;
    FlushBufferAndRunCallback_0200153c(data_ov073_020c4240->textLayer);
    FlushBufferAndRunCallback_0200153c(data_ov073_020c4240->titleLayer);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1f00;
    data_ov073_020c4240->restoreLayers = TRUE;
    data_ov073_020c4240->needsRedraw = TRUE;
    return 0;
}
