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

extern const TileIdPair data_ov073_020c40a8;
extern const TileTableSource data_ov073_020c40f0;
extern const TextFrame data_ov073_020c40d0;
extern const TextFrame data_ov073_020c4110;
extern StatusPanel *data_ov073_020c4260;
extern const char sOv073_UiBtlBtlLanguageP2_020c41dc[];

extern void InitTileTableFrom(void *table, const TileTableSource *source);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern Record *CloneRecord(Record **out, u32 id, int useTailAlloc, int heapTag);
extern void SetupStageParams(void *list, void *container, int arg);
extern u16 *UpdateScreenWidgetLayer(int widget);
extern BOOL InitTextLayerAt(void *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback(void *context);
extern int AcquireRecordSlot(int slot, int param);

void InitStatusPanel(StatusMenu *menu, StatusPanel *panel)
{
    TileIdPair ids = data_ov073_020c40a8;
    TileTableSource source = data_ov073_020c40f0;
    TextFrame titleFrame = data_ov073_020c40d0;
    TextFrame textFrame = data_ov073_020c4110;
    u16 *screenBase;

    source.ids = ids.ids;
    InitTileTableFrom(panel->uploads, &source);
    data_ov073_020c4260 = panel;
    panel->uploadsReady = TRUE;
    panel->selectedRecord = -1;
    panel->restoreLayers = FALSE;
    panel->messages = Msg_OpenContainerAndReadHeader(sOv073_UiBtlBtlLanguageP2_020c41dc, 0xe, FALSE);
    panel->record = NULL;
    CloneRecord(&panel->record, panel->recordId, 1, 0xe);
    SetupStageParams(menu->list, menu->container, 0);
    screenBase = UpdateScreenWidgetLayer(0x18);
    InitTextLayerAt(panel->titleLayer, 4, screenBase, menu->font, &titleFrame);
    DrawTextAnchored(panel->titleLayer, 0, 5, 2, 8, func_ov027_020ba2c8(menu->strings, 5));
    InitTextLayerAt(panel->textLayer, 4, screenBase, menu->font, &textFrame);
    FlushBufferAndRunCallback(panel->textLayer);
    AcquireRecordSlot(1, 1);
}
