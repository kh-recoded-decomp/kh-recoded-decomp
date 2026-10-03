#include "nitro/types.h"

typedef struct TileIdPair {
    int ids[2];
} TileIdPair;

typedef struct TileTableSource {
    int *ids;
    int count;
    u16 width;
    u16 height;
    u16 rowLength;
    u8 pad_0e[2];
} TileTableSource;

typedef struct TextFrame {
    u16 values[8];
} TextFrame;

typedef struct Record Record;

typedef struct StatusPanel {
    u8 pad_000[0x140];
    void *messages;
    Record *record;
    u8 uploads[0x16c - 0x148];
    BOOL uploadsReady;
    u8 pad_170[4];
    BOOL restoreLayers;
    u8 pad_178[0x198 - 0x178];
    u8 titleLayer[0x1cc - 0x198];
    u8 textLayer[0x200 - 0x1cc];
    int selectedRecord;
    u8 pad_204[4];
    u32 recordId;
} StatusPanel;

typedef struct StatusMenu {
    u8 pad_0000[0xdb8];
    void *font;
    u8 pad_0dbc[0x10e0 - 0xdbc];
    void *container;
    u8 pad_10e4[0x10f4 - 0x10e4];
    u8 list[0x11cc - 0x10f4];
    u8 strings[1];
} StatusMenu;

extern const TileIdPair data_ov073_020c4088;
extern const TileTableSource data_ov073_020c40d0;
extern const TextFrame data_ov073_020c40b0;
extern const TextFrame data_ov073_020c40f0;
extern StatusPanel *data_ov073_020c4240;
extern const char data_ov073_020c41bc[];

extern void InitTileTableFrom_020b9a0c(void *table, const TileTableSource *source);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern Record *CloneRecord_02051fc8(Record **out, u32 id, int useTailAlloc, int heapTag);
extern void func_ov039_020bdf10(void *list, void *container, int arg);
extern u16 *UpdateScreenWidgetLayer_020bc1e4(int widget);
extern BOOL InitTextLayerAt_020014b0(void *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern u16 *func_ov027_020ba2a8(void *table, int index);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern int AcquireRecordSlot_02051d3c(int slot, int param);

void InitStatusPanel_020c1488(StatusMenu *menu, StatusPanel *panel)
{
    TileIdPair ids = data_ov073_020c4088;
    TileTableSource source = data_ov073_020c40d0;
    TextFrame titleFrame = data_ov073_020c40b0;
    TextFrame textFrame = data_ov073_020c40f0;
    u16 *screenBase;

    source.ids = ids.ids;
    InitTileTableFrom_020b9a0c(panel->uploads, &source);
    data_ov073_020c4240 = panel;
    panel->uploadsReady = TRUE;
    panel->selectedRecord = -1;
    panel->restoreLayers = FALSE;
    panel->messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov073_020c41bc, 0xe, FALSE);
    panel->record = NULL;
    CloneRecord_02051fc8(&panel->record, panel->recordId, 1, 0xe);
    func_ov039_020bdf10(menu->list, menu->container, 0);
    screenBase = UpdateScreenWidgetLayer_020bc1e4(0x18);
    InitTextLayerAt_020014b0(panel->titleLayer, 4, screenBase, menu->font, &titleFrame);
    DrawTextAnchored_020015a0(panel->titleLayer, 0, 5, 2, 8, func_ov027_020ba2a8(menu->strings, 5));
    InitTextLayerAt_020014b0(panel->textLayer, 4, screenBase, menu->font, &textFrame);
    FlushBufferAndRunCallback_0200153c(panel->textLayer);
    AcquireRecordSlot_02051d3c(1, 1);
}
