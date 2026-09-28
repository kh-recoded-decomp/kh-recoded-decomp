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
extern TitlePaths data_ov000_0206393c;
extern u16 data_ov000_02063a00[];
extern u16 data_02055ba0[];
extern char OVERLAY_27_ID_0000001b[];

#define FS_OVERLAY_ID_ov027 ((u32)OVERLAY_27_ID_0000001b)

extern void func_02029f78(int processor, int overlayId);
extern void func_02029f98(int processor, int overlayId);
extern void func_ov000_02061b88(int value, int waitVBlank);
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0as3d);
extern void *G2_GetBG3ScrPtr_02006f80(void);
extern void *func_01ff8740(u32 value, void *dest, u32 size);
extern void func_ov027_020ba25c(MessageSet *messages, const char *path, int compressed);
extern int func_0202b788(void);
extern int func_02001458(FontResource *font, const char *path);
extern void func_02007250(const void *palette, u32 paletteOffset, u32 size);
extern BOOL InitTextLayerDefault_02001494(TextLayer *layer, int bgLayer, FontResource *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int color);
extern const u16 *func_ov027_020ba2a8(MessageSet *messages, int index);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(TextLayer *layer);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void OS_WaitVBlankIntr_020049d0(void);
extern BOOL DestroyFndObjectList_020014f0(TextLayer *layer);
extern void func_02001474(FontResource *font);
extern void FreePointerIfSet_020ba294(void **pointer);

#define REG_BG3CNT (*(vu16 *)0x0400000e)
#define REG_POWCNT (*(vu16 *)0x04000304)
#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

void ShowTitleNotice_02061fc0(void *owner, int noticeType)
{
    FontResource font;
    TextLayer layer;
    TextFrame frame = data_ov000_020637a4;
    MessageSet messages;

    func_02029f78(0, FS_OVERLAY_ID_ov027);
    func_ov000_02061b88(-0x10, 1);
    GX_SetBankForBG_02008358(0x10);
    GX_SetBankForBGExtPltt_0200868c(0);
    GX_SetGraphicsMode_020066c4(1, 0, 1);
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | 0x204);
    func_01ff8740(0, G2_GetBG3ScrPtr_02006f80(), 0x600);
    func_ov027_020ba25c(&messages, data_ov000_0206393c.messageArchive, 0);
    func_02001458(&font, func_0202b788() != 0 ? data_ov000_0206393c.fontEu : data_ov000_0206393c.fontJp);
    func_02007250(data_ov000_02063a00, 0, 2);
    func_02007250(data_02055ba0, 0x1a0, 0x20);
    REG_POWCNT |= 0x8000;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x800;
    REG_DB_DISPCNT = REG_DB_DISPCNT & ~0x1f00;
    InitTextLayerDefault_02001494(&layer, 3, &font, &frame);
    CallVirtualHandlerSlot1_02001574(&layer, 0);
    switch (noticeType) {
    case 0:
        DrawTextAnchored_020015a0(&layer, 0x78, 0x46, 1, 0x10, func_ov027_020ba2a8(&messages, 3));
        break;
    case 1:
        DrawTextAnchored_020015a0(&layer, 0x78, 0x3c, 1, 0x10, func_ov027_020ba2a8(&messages, 0));
        DrawTextAnchored_020015a0(&layer, 0x78, 0x5a, 1, 0x10, func_ov027_020ba2a8(&messages, 2));
        break;
    case 2:
        DrawTextAnchored_020015a0(&layer, 0x78, 0x3c, 1, 0x10, func_ov027_020ba2a8(&messages, 1));
        DrawTextAnchored_020015a0(&layer, 0x78, 0x5a, 1, 0x10, func_ov027_020ba2a8(&messages, 2));
        break;
    }
    FlushBufferAndRunCallback_0200153c(&layer);
    SetBrightnessAndSyncMain_02029e7c(0);
    OS_WaitVBlankIntr_020049d0();
    DestroyFndObjectList_020014f0(&layer);
    func_02001474(&font);
    FreePointerIfSet_020ba294(&messages.file);
    func_02029f98(0, FS_OVERLAY_ID_ov027);
}
