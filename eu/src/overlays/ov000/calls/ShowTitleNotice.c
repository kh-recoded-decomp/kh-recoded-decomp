#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct MessageSet {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct FontResource {
    void *info;
    void *splitter;
    void *file;
} FontResource;

typedef struct TextLayer {
    u8 data[0x34];
} TextLayer;

typedef struct TitlePaths {
    char messageArchive[0x10];
    char fontEu[0x18];
    char fontJp[0x18];
} TitlePaths;

extern const TextFrame data_ov000_020637a4;
extern TitlePaths sOv000_TtlTitleLanguageSZ_0206393c;
extern u16 data_ov000_02063a00[];
extern u16 gTitleNoticePalette[];
extern char OVERLAY_27_ID[];

#define FS_OVERLAY_ID_ov027 ((u32)OVERLAY_27_ID)

extern void func_02029f8c(int processor, int overlayId);
extern void func_02029fac(int processor, int overlayId);
extern void func_ov000_02061b88(int value, int waitVBlank);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0as3d);
extern void *G2_GetBG3ScrPtr(void);
extern void *MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void LoadPackedFileView(MessageSet *messages, const char *path, int compressed);
extern int GetLanguageIndex(void);
extern int func_0200146c(FontResource *font, const char *path);
extern void GX_LoadBGPltt(const void *palette, u32 paletteOffset, u32 size);
extern BOOL InitTextLayerDefault(TextLayer *layer, int bgLayer, FontResource *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int color);
extern const u16 *func_ov027_020ba2c8(MessageSet *messages, int index);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern void SetBrightnessAndSyncMain(int brightness);
extern void OS_WaitVBlankIntr(void);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern void FreeResourceBufferAndProbeHeap(FontResource *font);
extern void FreePointerIfSet(void **pointer);

#define REG_BG3CNT (*(vu16 *)0x0400000e)
#define REG_POWCNT (*(vu16 *)0x04000304)
#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

void ShowTitleNotice(void *owner, int noticeType)
{
    FontResource font;
    TextLayer layer;
    TextFrame frame = data_ov000_020637a4;
    MessageSet messages;

    func_02029f8c(0, FS_OVERLAY_ID_ov027);
    func_ov000_02061b88(-0x10, 1);
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    GX_SetGraphicsMode(1, 0, 1);
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x204);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x600);
    LoadPackedFileView(&messages, sOv000_TtlTitleLanguageSZ_0206393c.messageArchive, 0);
    func_0200146c(&font, GetLanguageIndex() != 0 ? sOv000_TtlTitleLanguageSZ_0206393c.fontEu : sOv000_TtlTitleLanguageSZ_0206393c.fontJp);
    GX_LoadBGPltt(data_ov000_02063a00, 0, 2);
    GX_LoadBGPltt(gTitleNoticePalette, 0x1a0, 0x20);
    REG_POWCNT |= 0x8000;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x800;
    REG_DB_DISPCNT = REG_DB_DISPCNT & ~0x1f00;
    InitTextLayerDefault(&layer, 3, &font, &frame);
    CallVirtualHandlerSlot1(&layer, 0);
    switch (noticeType) {
    case 0:
        DrawTextAnchored(&layer, 0x78, 0x46, 1, 0x10, func_ov027_020ba2c8(&messages, 3));
        break;
    case 1:
        DrawTextAnchored(&layer, 0x78, 0x3c, 1, 0x10, func_ov027_020ba2c8(&messages, 0));
        DrawTextAnchored(&layer, 0x78, 0x5a, 1, 0x10, func_ov027_020ba2c8(&messages, 2));
        break;
    case 2:
        DrawTextAnchored(&layer, 0x78, 0x3c, 1, 0x10, func_ov027_020ba2c8(&messages, 1));
        DrawTextAnchored(&layer, 0x78, 0x5a, 1, 0x10, func_ov027_020ba2c8(&messages, 2));
        break;
    }
    FlushBufferAndRunCallback(&layer);
    SetBrightnessAndSyncMain(0);
    OS_WaitVBlankIntr();
    DestroyFndObjectList(&layer);
    FreeResourceBufferAndProbeHeap(&font);
    FreePointerIfSet(&messages.file);
    func_02029fac(0, FS_OVERLAY_ID_ov027);
}
