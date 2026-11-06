#include "src/overlays/ov027/WidgetRecordOps.h"
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
extern SlotPoolConfig gScoreScreenWidgetConfig;
extern TextFrame gScoreScreenTextLayer0Frame;
extern TextFrame gScoreScreenTextLayer1Frame;
extern char sOv083_UiMenuStrLanguageShopSZ_020bf6e0[];

extern void MI_CpuFill8(void *dest, int value, u32 size);
extern void GXS_SetGraphicsMode(int mode);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern PlayerStats *GetOverlaySelectionRecord(int index);
extern void ComputePlayerStats(u8 *state, PlayerStats *out, BOOL recompute, int scale);
extern u64 OS_GetTick(void);
extern u64 GetCardThreadStartTick(void);
extern u64 _ll_udiv(u64 dividend, u64 divisor);
extern u16 *UpdateScreenWidgetLayer(int screen);
extern void LoadPackedFileView(void *view, const char *path, BOOL fromTail);
extern void *GetMenuFont10(void);
extern BOOL InitTextLayerAt(TextLayer *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void FillBackgroundLayerRect(TextLayer *info, u16 *dst, int x, int y, u8 palette);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void *GetSecondaryMenuElement(void);
extern void *GetMenuWidgetContainer(void);
extern u32 BuildSlotImageParams(int slot, u32 low);
extern void InitObjManagerAndMark(void *container, SlotPoolConfig *config);
extern void CreateWidgetImageEntry(void *container, u32 imageParams);
extern void LoadWidgetDescriptorsFromFile(void *container, u32 imageParams, int count);
extern void LoadTagTrackerResourceFile(void *elements, u32 imageParams);
extern void *FindWidgetById(void *container, int id);
extern int *GetWidgetPosition(void *container, void *widget);
extern s16 SetWidgetDigitDisplay(void *cells, int widgetId, int key, u32 value);
extern s16 DrawWidgetPlayTime(void *cells, int widgetId, int key, u32 value);
extern void LoadSubBgAndTriggerTags(int a, int b, int c, int d, int e);
extern BOOL GetMenuStackDepth(void);
extern BOOL GetPreviousMenuStackEntry(void);
extern void *Archive_LoadFile(u32 fileId, int mode);
extern void GetBgDataFromArchive(void *dst, void *file, int x, int y, int flags);
extern void DC_FlushRange(void *dest, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);

BOOL InitScoreScreen(ScoreScreen *screen)
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

    MI_CpuFill8(screen, 0, sizeof(ScoreScreen));
    GXS_SetGraphicsMode(0);
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
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0x20);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x600);
    screen->dirty = 2;

    base = *GetOverlaySelectionRecord(0);
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
    ComputePlayerStats(data_0205fe0c, &stats, TRUE, 0);
    screen->elapsedSeconds = *(int *)(data_0205fe0c + 0x28c8)
        + _ll_udiv((OS_GetTick() - GetCardThreadStartTick()) * 64, 0x1ff6210);

    frameA = gScoreScreenTextLayer0Frame;
    frameB = gScoreScreenTextLayer1Frame;
    layer = UpdateScreenWidgetLayer(0x19);
    LoadPackedFileView(screen->strings, sOv083_UiMenuStrLanguageShopSZ_020bf6e0, FALSE);
    InitTextLayerAt(&screen->textLayers[0], 5, layer, GetMenuFont10(), &frameA);
    InitTextLayerAt(&screen->textLayers[1], 5, layer, GetMenuFont10(), &frameB);
    FillBackgroundLayerRect(&screen->textLayers[0], layer, frameA.x, frameA.y, 0xf);
    FillBackgroundLayerRect(&screen->textLayers[1], layer, frameB.x, frameB.y, 0xf);
    func_01ff8ad8(layer, screen->tileBuffer, 0x600);

    elements = GetSecondaryMenuElement();
    container = GetMenuWidgetContainer();
    config = gScoreScreenWidgetConfig;
    config.imageParams = BuildSlotImageParams(2, 2);
    InitObjManagerAndMark(container, &config);
    CreateWidgetImageEntry(container, BuildSlotImageParams(3, 1));
    LoadWidgetDescriptorsFromFile(container, BuildSlotImageParams(2, 6), 0x16);
    LoadTagTrackerResourceFile(elements, BuildSlotImageParams(2, 5));
    screen->widgets[0] = FindWidgetById(container, 0x16);
    screen->widgets[1] = FindWidgetById(container, 2);
    screen->widgets[2] = FindWidgetById(container, 0xd);
    screen->widgets[3] = FindWidgetById(container, 0xe);
    screen->widgets[4] = FindWidgetById(container, 0xf);
    screen->widgets[5] = FindWidgetById(container, 0x10);
    screen->widgets[6] = FindWidgetById(container, 0x11);
    screen->widgets[7] = FindWidgetById(container, 0x12);
    screen->widgets[8] = FindWidgetById(container, 0x13);

    rowWidget = FindWidgetById(container, 5);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(rowWidget), 2);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 6)), 2);
    columnWidget = FindWidgetById(container, 8);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(columnWidget), 2);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 9)), 2);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 10)), 2);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 11)), 2);
    SetWidgetRecordMode(container, (const struct WidgetPositionRecord *)(FindWidgetById(container, 12)), 2);
    screen->row = (GetWidgetPosition(container, rowWidget)[1] >> 12) - 13;
    screen->labelColumn = 0;
    screen->valueColumn = (GetWidgetPosition(container, columnWidget)[0] >> 12) - 16;

    screen->bestDigits = SetWidgetDigitDisplay(container, 0x14, 8, *(u32 *)(data_0205fe0c + 0x28d0));
    screen->timerDigits = DrawWidgetPlayTime(container, 1, 1, screen->elapsedSeconds);
    screen->digitsB = SetWidgetDigitDisplay(container, 0x15, 9, 0);
    screen->digitsC = SetWidgetDigitDisplay(container, 0, 0, 0);
    screen->cells = container;
    screen->records = elements;

    LoadSubBgAndTriggerTags(2, 0, 0, 1, 0);
    if (GetMenuStackDepth() && GetPreviousMenuStackEntry()) {
        screen->bgFile = Archive_LoadFile(BuildSlotImageParams(2, 0), 0xe);
        GetBgDataFromArchive(screen->bgData, screen->bgFile, -1, -1, 0);
        DC_FlushRange((void *)0x05000400, 0x40);
        GXS_LoadBGPltt(screen->palette->data + 0x40, 0, 0x40);
    }
    return TRUE;
}
