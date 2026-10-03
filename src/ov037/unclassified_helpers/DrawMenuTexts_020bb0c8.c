#include "nitro/types.h"

typedef struct TextFrame {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 palette;
    s16 pad_0a[3];
} TextFrame;

typedef struct TitleIdTable {
    s32 ids[8];
} TitleIdTable;

typedef struct FontResource {
    u32 words[3];
} FontResource;

typedef struct TextLayer {
    u8 data[0x34];
} TextLayer;

typedef struct PackedFileView {
    u32 words[3];
} PackedFileView;

typedef struct MenuEntry {
    s32 id;
    s32 textId;
} MenuEntry;

typedef struct Ov037Context {
    u16 selected;
    u16 entryCount;
    s32 rowOffset;
    u8 list[0x4c];
    u8 tileTable[0x1c];
    u8 model[0x128];
    u8 camera[0x38];
    s32 enabled;
    MenuEntry entries[4];
    TextLayer text;
} Ov037Context;

extern Ov037Context *g_ov037Context_020bb764;
extern const TextFrame data_ov037_020bb64c;
extern const TitleIdTable data_ov037_020bb670;
extern char g_menuFontPath_020bb738[];
extern char g_menuTextArchive_020bb750[];
extern u16 *UpdateWidgetLayerDefault_020b9df0(void *tileTable, int row);
extern int func_02001458(FontResource *font, char *path);
extern BOOL InitTextLayerAt_020014b0(TextLayer *layer, int plane, u16 *screen, FontResource *font, TextFrame *frame);
extern void LoadPackedFileView_020ba25c(PackedFileView *view, char *path, BOOL fromTail);
extern void *func_ov027_020ba2a8(PackedFileView *view, int index);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const void *text);
extern void FlushBufferAndRunCallback_0200153c(TextLayer *layer);
extern void DestroyFndObjectList_020014f0(TextLayer *layer);
extern s8 GetCtxModeByte_02068084(void);
extern s32 func_ov037_020bad0c(void);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(FontResource *font);
extern void FreePointerIfSet_020ba294(PackedFileView *view);
extern void MarkTileTableRowDirty_020b9e00(void *tileTable, int row);

void DrawMenuTexts_020bb0c8(void)
{
    TextFrame frame = data_ov037_020bb64c;
    FontResource font;
    TextLayer layer;
    PackedFileView view;
    TitleIdTable titleIds;
    u16 *screen;
    int index;
    int mode;
    s32 titleIndex;

    titleIds = data_ov037_020bb670;
    frame.y = g_ov037Context_020bb764->rowOffset;
    frame.height = 0x18 - g_ov037Context_020bb764->rowOffset;
    screen = UpdateWidgetLayerDefault_020b9df0(g_ov037Context_020bb764->tileTable, 10);
    func_02001458(&font, g_menuFontPath_020bb738);
    InitTextLayerAt_020014b0(&layer, 2, screen, &font, &frame);
    LoadPackedFileView_020ba25c(&view, g_menuTextArchive_020bb750, TRUE);
    for (index = 0; index < g_ov037Context_020bb764->entryCount; index++) {
        DrawTextAnchored_020015a0(&layer, 0x38, index * 16 + 3, 2, 0x411,
                                  func_ov027_020ba2a8(&view, g_ov037Context_020bb764->entries[index].textId));
    }
    FlushBufferAndRunCallback_0200153c(&layer);
    DestroyFndObjectList_020014f0(&layer);
    frame.x = 0;
    frame.y = 2;
    frame.width = 0x20;
    frame.height = 4;
    frame.palette = 0x8d;
    mode = GetCtxModeByte_02068084();
    titleIndex = func_ov037_020bad0c();
    InitTextLayerAt_020014b0(&g_ov037Context_020bb764->text, 2, screen, &font, &frame);
    FlushBufferAndRunCallback_0200153c(&g_ov037Context_020bb764->text);
    if (titleIndex >= 0) {
        DrawTextAnchored_020015a0(&g_ov037Context_020bb764->text, 0x80, 0x10, 2, 0x212,
                                  func_ov027_020ba2a8(&view, titleIndex + titleIds.ids[mode]));
    }
    FreeResourceBufferAndProbeHeap_02001474(&font);
    FreePointerIfSet_020ba294(&view);
    MarkTileTableRowDirty_020b9e00(g_ov037Context_020bb764->tileTable, 10);
}
