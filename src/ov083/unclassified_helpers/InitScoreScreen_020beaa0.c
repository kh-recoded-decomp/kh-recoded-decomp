#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 rest[6];
} TextFrame;

typedef struct SlotPoolConfig {
    u32 imageParams;
    u32 rest[3];
} SlotPoolConfig;

typedef struct PlayerStats {
    u8 unk_0;
    u8 level;
    u16 unk_2;
    u16 hp;
    u16 strength;
    u16 magic;
    u16 defense;
    u16 unk_C;
} PlayerStats;

typedef struct ScoreEvent {
    int type;
    int value;
} ScoreEvent;

typedef struct Palette {
    u8 pad_00[0xc];
    u8 *data;
} Palette;

typedef struct ScoreScreen {
    u8 pad0;
    u8 dirty;
    u8 pad2;
    u8 eventCount;
    u16 bestDigits;
    u16 timerDigits;
    u16 digitsB;
    u16 digitsC;
    int elapsedSeconds;
    ScoreEvent events[16];
    u8 row;
    u8 labelColumn;
    u8 valueColumn;
    u8 pad93[5];
    u16 baseA;
    u16 baseB;
    u16 baseC;
    u16 baseD;
    u16 baseE;
    u16 baseF;
    u8 padA4[0xa];
    s16 limitB;
    s16 limitC;
    s16 limitD;
    s16 limitE;
    s16 limitF;
    TextLayer textLayers[2];
    u8 pad120[4];
    void *records;
    void *cells;
    void *widgets[9];
    u8 strings[0xc];
    u8 bgData[8];
    Palette *palette;
    void *bgFile;
    u8 tileBuffer[0x600];
} ScoreScreen;

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT  (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT  (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT  (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT  (*(vu16 *)0x0400100e)
#define REG_DB_BG3OFS  (*(vu32 *)0x0400101c)

extern u8 *data_0205fe0c;
extern SlotPoolConfig data_ov083_020bf64c;
extern TextFrame data_ov083_020bf65c;
extern TextFrame data_ov083_020bf66c;
extern char data_ov083_020bf6c0[];

extern void func_01ff8830(void *dest, int value, u32 size);
extern void func_0200672c(int mode);
extern void *G2S_GetBG1CharPtr_02007100(void);
extern void *G2S_GetBG1ScrPtr_02006e68(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern PlayerStats *func_0204f768(int index);
extern void ComputePlayerStats_02050b30(u8 *state, PlayerStats *out, BOOL recompute, int scale);
extern u64 func_02003fd4(void);
extern u64 GetCardThreadStartTick_0202726c(void);
extern u64 func_02023d54(u64 dividend, u64 divisor);
extern u16 *UpdateScreenWidgetLayer_020bc1e4(int screen);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern void *func_ov039_020bc994(void);
extern BOOL InitTextLayerAt_020014b0(TextLayer *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void FillBackgroundLayerRect_02001a60(TextLayer *info, u16 *dst, int x, int y, u8 palette);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void *func_ov039_020bc1a4(void);
extern void *func_ov039_020bc1cc(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void InitObjManagerAndMark_020b9060(void *container, SlotPoolConfig *config);
extern void PXI_Init_020b9078(void *container, u32 imageParams);
extern void func_ov027_020b8f98(void *container, u32 imageParams, int count);
extern void func_ov027_020b7e24(void *elements, u32 imageParams);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern void func_ov027_020b97b8(void *container, void *widget, int mode);
extern int *func_ov027_020b91a8(void *container, void *widget);
extern s16 SetWidgetDigitDisplay_020be234(void *cells, int widgetId, int key, u32 value);
extern s16 func_ov039_020be358(void *cells, int widgetId, int key, u32 value);
extern void func_ov039_020bc488(int a, int b, int c, int d, int e);
extern BOOL func_ov039_020bc810(void);
extern BOOL func_ov039_020bc84c(void);
extern void *func_0202c478(u32 fileId, int mode);
extern void GetBgDataFromArchive_0202b554(void *dst, void *file, int x, int y, int flags);
extern void func_0200344c(void *dest, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);

BOOL InitScoreScreen_020beaa0(ScoreScreen *screen)
{
    PlayerStats base;
    PlayerStats stats;
    TextFrame frameB;
    TextFrame frameA;
    SlotPoolConfig config;
    u16 *layer;
    void *elements;
    void *container;
    void *rowWidget;
    void *columnWidget;

    func_01ff8830(screen, 0, sizeof(ScoreScreen));
    func_0200672c(0);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1f00;
    REG_DB_BG0CNT = (u16)((REG_DB_BG0CNT & 0x43) | (0xc << 8));
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & 0x43) | (0xd << 8));
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & 0x43) | (0xe << 8));
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & 0x43) | (0xf << 8));
    REG_DB_BG0CNT = (u16)(REG_DB_BG0CNT & ~3);
    REG_DB_BG1CNT = (u16)((REG_DB_BG1CNT & ~3) | 1);
    REG_DB_BG2CNT = (u16)((REG_DB_BG2CNT & ~3) | 2);
    REG_DB_BG3CNT = (u16)((REG_DB_BG3CNT & ~3) | 3);
    REG_DB_BG3OFS = 0;
    MIi_CpuClearFast_01ff8740(0, G2S_GetBG1CharPtr_02007100(), 0x20);
    MIi_CpuClearFast_01ff8740(0, G2S_GetBG1ScrPtr_02006e68(), 0x600);
    screen->dirty = 2;

    base = *func_0204f768(0);
    screen->baseB = base.hp;
    screen->baseA = base.unk_2;
    screen->baseC = base.strength;
    screen->baseD = base.magic;
    screen->baseE = base.defense;
    screen->baseF = base.unk_C;
    screen->limitB = 400;
    screen->limitC = 200;
    screen->limitD = 200;
    screen->limitE = 200;
    screen->limitF = 14;
    screen->eventCount = 1;
    screen->events[0].type = 0;
    screen->events[1].type = 0;
    ComputePlayerStats_02050b30(data_0205fe0c, &stats, TRUE, 0);
    screen->elapsedSeconds = *(int *)(data_0205fe0c + 0x28c8)
        + func_02023d54((func_02003fd4() - GetCardThreadStartTick_0202726c()) * 64, 0x1ff6210);

    frameA = data_ov083_020bf65c;
    frameB = data_ov083_020bf66c;
    layer = UpdateScreenWidgetLayer_020bc1e4(0x19);
    LoadPackedFileView_020ba25c(screen->strings, data_ov083_020bf6c0, FALSE);
    InitTextLayerAt_020014b0(&screen->textLayers[0], 5, layer, func_ov039_020bc994(), &frameA);
    InitTextLayerAt_020014b0(&screen->textLayers[1], 5, layer, func_ov039_020bc994(), &frameB);
    FillBackgroundLayerRect_02001a60(&screen->textLayers[0], layer, frameA.x, frameA.y, 0xf);
    FillBackgroundLayerRect_02001a60(&screen->textLayers[1], layer, frameB.x, frameB.y, 0xf);
    func_01ff8ad8(layer, screen->tileBuffer, 0x600);

    elements = func_ov039_020bc1a4();
    container = func_ov039_020bc1cc();
    config = data_ov083_020bf64c;
    config.imageParams = BuildSlotImageParams_020bc220(2, 2);
    InitObjManagerAndMark_020b9060(container, &config);
    PXI_Init_020b9078(container, BuildSlotImageParams_020bc220(3, 1));
    func_ov027_020b8f98(container, BuildSlotImageParams_020bc220(2, 6), 0x16);
    func_ov027_020b7e24(elements, BuildSlotImageParams_020bc220(2, 5));
    screen->widgets[0] = FindWidgetById_020b90a4(container, 0x16);
    screen->widgets[1] = FindWidgetById_020b90a4(container, 2);
    screen->widgets[2] = FindWidgetById_020b90a4(container, 0xd);
    screen->widgets[3] = FindWidgetById_020b90a4(container, 0xe);
    screen->widgets[4] = FindWidgetById_020b90a4(container, 0xf);
    screen->widgets[5] = FindWidgetById_020b90a4(container, 0x10);
    screen->widgets[6] = FindWidgetById_020b90a4(container, 0x11);
    screen->widgets[7] = FindWidgetById_020b90a4(container, 0x12);
    screen->widgets[8] = FindWidgetById_020b90a4(container, 0x13);

    rowWidget = FindWidgetById_020b90a4(container, 5);
    func_ov027_020b97b8(container, rowWidget, 2);
    func_ov027_020b97b8(container, FindWidgetById_020b90a4(container, 6), 2);
    columnWidget = FindWidgetById_020b90a4(container, 8);
    func_ov027_020b97b8(container, columnWidget, 2);
    func_ov027_020b97b8(container, FindWidgetById_020b90a4(container, 9), 2);
    func_ov027_020b97b8(container, FindWidgetById_020b90a4(container, 10), 2);
    func_ov027_020b97b8(container, FindWidgetById_020b90a4(container, 11), 2);
    func_ov027_020b97b8(container, FindWidgetById_020b90a4(container, 12), 2);
    screen->row = (func_ov027_020b91a8(container, rowWidget)[1] >> 12) - 13;
    screen->labelColumn = 0;
    screen->valueColumn = (func_ov027_020b91a8(container, columnWidget)[0] >> 12) - 16;

    screen->bestDigits = SetWidgetDigitDisplay_020be234(container, 0x14, 8, *(u32 *)(data_0205fe0c + 0x28d0));
    screen->timerDigits = func_ov039_020be358(container, 1, 1, screen->elapsedSeconds);
    screen->digitsB = SetWidgetDigitDisplay_020be234(container, 0x15, 9, 0);
    screen->digitsC = SetWidgetDigitDisplay_020be234(container, 0, 0, 0);
    screen->cells = container;
    screen->records = elements;

    func_ov039_020bc488(2, 0, 0, 1, 0);
    if (func_ov039_020bc810() && func_ov039_020bc84c()) {
        screen->bgFile = func_0202c478(BuildSlotImageParams_020bc220(2, 0), 0xe);
        GetBgDataFromArchive_0202b554(screen->bgData, screen->bgFile, -1, -1, 0);
        func_0200344c((void *)0x05000400, 0x40);
        GXS_LoadBGPltt_020072b4(screen->palette->data + 0x40, 0, 0x40);
    }
    return TRUE;
}
