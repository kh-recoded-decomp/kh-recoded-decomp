#include "nitro/types.h"

typedef struct CellPos {
    int x;
    int y;
} CellPos;

typedef struct TextFrame {
    u16 values[8];
} TextFrame;

typedef struct ObjConfig {
    u32 words[4];
} ObjConfig;

typedef struct PlayerStats {
    u8 data[0x10];
} PlayerStats;

typedef struct StatusMenu StatusMenu;

typedef void (*PageFunc)(StatusMenu *menu, void *page);

typedef struct PageHandlers {
    PageFunc open;
    PageFunc update;
    PageFunc draw;
    PageFunc close;
    void *page;
} PageHandlers;

typedef struct SaveData {
    u8 pad_0000[0x28c8];
    int heartCount;
    u32 experience;
    int munny;
    s8 levelBonus;
} SaveData;

struct StatusMenu {
    s8 page;
    u8 loaded;
    u8 shown;
    u8 pad_03;
    u16 munnyDigits;
    u16 timeDigits;
    int heartCount;
    int playSeconds;
    u8 pad_10[0x1c - 0x10];
    BOOL isCurrent;
    BOOL showExtra;
    BOOL wirelessMode;
    BOOL eventsLocked;
    u8 statText[0x12c - 0x2c];
    void *recordA;
    void *recordB;
    void *recordC;
    void *recordD;
    s16 headerCells[6];
    u8 pad_148[0x16c - 0x148];
    u8 recordList[0x1f4 - 0x16c];
    CellPos rowPos[5];
    void *recordE;
    void *rowWidget;
    s16 rowCellsA[7];
    s16 rowCellsB[7];
    s16 rowCellsC[7];
    u8 pad_24e[2];
    u8 progressList[0xa54 - 0x250];
    void *recordF;
    void *progressWidget;
    u8 columns[0xb3c - 0xa5c];
    void *recordG;
    void *columnWidget;
    u8 details[0xd4c - 0xb44];
    int selection;
    PageHandlers handlers[5];
    int *mapLayout;
    void *font;
    void *fontAlt;
    u8 textLayers[3][0x34];
    u8 pad_e5c[0x10dc - 0xe5c];
    void *recordPool;
    void *widgets;
    u8 pad_10e4[0x10ec - 0x10e4];
    void *listWidget;
    void *scrollWidget;
    u8 list[7];
    u8 listRows;
    u8 pad_10fc[0x1118 - 0x10fc];
    u16 listX;
    u16 listWidth;
    u8 pad_111c[0x11cc - 0x111c];
    u8 strings[0xc];
    void *titleText;
    void *subtitleText;
    s16 rowCellsD[7];
    s16 slotCells[7][4];
    s64 openTick;
};

extern SaveData *data_0205fe0c;
extern const ObjConfig data_ov073_020c40e0;
extern const TextFrame data_ov073_020c4120;
extern const TextFrame data_ov073_020c40c0;
extern const TextFrame data_ov073_020c4100;
extern const char sOv073_UiMenuStrLanguageStatusSZ_020c41b8[];

extern int GetMenuSelection(void);
extern int GetRuntimeStateFlags(void);
extern void MI_CpuFill8(void *dest, int value, int size);
extern int GetCurrentSceneId(void);
extern u8 *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern BOOL AcquireRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern void GXS_SetGraphicsMode(int mode);
extern void *G2S_GetBG1CharPtr(void);
extern void MIi_CpuClearFast(int value, void *dest, int size);
extern void *GetSecondaryMenuElement(void);
extern void *GetMenuWidgetContainer(void);
extern u32 BuildSlotImageParams(int slot, unsigned int low);
extern void InitObjManagerAndMark(void *obj, void *config);
extern void func_ov027_020b9098(void *widgets, u32 params);
extern void func_ov027_020b8fb8(void *widgets, u32 params, int count);
extern void func_ov027_020b7e44(void *pool, u32 params);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b82a4(void *pool, void *record, int mode);
extern void *FindWidgetById(void *root, int id);
extern void func_ov027_020b97d8(void *widgets, void *widget, int mode);
extern void func_ov027_020b9604(void *widgets, void *widget);
extern void CreateContainerCells(void *container, s16 *cells, int cellId, int count);
extern CellPos *GetWidgetPosition(void *widgets, void *widget);
extern void IndexedRecord_SetPair(void *widgets, int index, CellPos *pos);
extern void IndexedRecords_SetFlag2(void *widgets, int index, int value);
extern u64 OS_GetTick(void);
extern s64 GetCardThreadStartTick(void);
extern s16 SetWidgetDigitDisplay(void *cells, int widgetId, int key, u32 value);
extern s16 func_ov039_020be378(void *cells, int widgetId, int key, u32 value);
extern void func_ov034_020bdea4(void *list, void *widgets, int x, int y, int rows, int a, int b, int c, int d);
extern u16 *UpdateScreenWidgetLayer(int widget);
extern void *GetMenuFont10(void);
extern void *GetMenuFont08(void);
extern void LoadPackedFileView(void *view, const char *path, BOOL fromTail);
extern void ResetStatusHeaderText(StatusMenu *menu);
extern void *func_ov027_020ba2c8(void *strings, int index);
extern BOOL InitTextLayerAt(void *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void LoadStatusLabels(StatusMenu *menu);
extern int *AcquireMapLayout(BOOL reload, BOOL discard);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void ComputePlayerStats(SaveData *save, PlayerStats *out, BOOL recompute, int scale);
extern void RefreshStatusMenuData(SaveData *save, void *preview);
extern int GetFieldCad0(void);
extern int GetMenuStackDepth(void);
extern void LoadSlotSubBgImage(int a, int b, int c, u16 d);
extern void ResetStatusPageState(StatusMenu *menu);
extern void SetEntrySlotsVisible(void *widgets, void *widget, int visible);
extern void RuntimeState_SetCondition(BOOL flag);

extern void OpenStatusPageView(StatusMenu *menu, void *page);
extern void func_ov073_020bff88(StatusMenu *menu, void *page);
extern void DrawStatusPanel(StatusMenu *menu, void *page);
extern void HideStatusPageIcons(StatusMenu *menu, void *page);
extern void SetupStatusPageScroll(StatusMenu *menu, void *page);
extern void HandleSlotListInput(StatusMenu *menu, void *page);
extern void func_ov073_020c0710(StatusMenu *menu, void *page);
extern void HideStatusPageRows(StatusMenu *menu, void *page);
extern void SetupStatusScreenScroll(StatusMenu *menu, void *page);
extern void UpdateStatusListInput(StatusMenu *menu, void *page);
extern void func_ov073_020c0ed8(StatusMenu *menu, void *page);
extern void HideStatusScreenElement(StatusMenu *menu, void *page);
extern void SetupStatusPanelScroll(StatusMenu *menu, void *page);
extern void UpdateStatusPanelInput(StatusMenu *menu, void *page);
extern void func_ov073_020c111c(StatusMenu *menu, void *page);
extern void HideStatusPanelElement(StatusMenu *menu, void *page);
extern void InitStatusPanel(StatusMenu *menu, void *page);
extern void UpdateStatusPanel(StatusMenu *menu, void *page);
extern void LoadStatusScreenResources(StatusMenu *menu, void *page);
extern void CloseStatusScreen(StatusMenu *menu, void *page);

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)
#define REG_DB_BG2OFS (*(vu32 *)0x04001018)
#define REG_POWCNT (*(vu16 *)0x04000304)

int InitStatusMenu(StatusMenu *menu)
{
    int i;
    BOOL inSpecialMode;
    BOOL fromSpecialEntry;
    void *pool;
    void *widgets;
    void *widget;
    u16 *screenBase;
    PageHandlers *handlers;
    int value;
    PlayerStats stats;
    ObjConfig config;
    TextFrame frameC;
    TextFrame frameB;
    TextFrame frameA;
    CellPos pos;

    inSpecialMode = GetMenuSelection() == 3;
    fromSpecialEntry = GetRuntimeStateFlags() == 0x4100;
    MI_CpuFill8(menu, 0, sizeof(StatusMenu));
    menu->wirelessMode = GetMenuSelection() == 3 && GetCurrentSceneId() == 1;
    i = 0;
    menu->selection = GetOverlaySelectionRecord(0)[0x10];
    AcquireRecordManager();
    AcquireRecordSlot(3, 1);
    GXS_SetGraphicsMode(0);

    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1e00;
    REG_DB_BG0CNT = (REG_DB_BG0CNT & 0x43) | 0xc00;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & 0x43) | 0xd00;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & 0x43) | 0xe00;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0xf00;
    REG_DB_BG0CNT = (REG_DB_BG0CNT & ~3) | 0;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~3) | 1;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~3) | 2;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & ~3) | 3;
    REG_DB_BG2OFS = 0;
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0x20);

    pool = GetSecondaryMenuElement();
    widgets = GetMenuWidgetContainer();
    config = data_ov073_020c40e0;
    config.words[0] = BuildSlotImageParams(0, 1);
    InitObjManagerAndMark(widgets, &config);
    func_ov027_020b9098(widgets, BuildSlotImageParams(1, 2));
    func_ov027_020b8fb8(widgets, BuildSlotImageParams(0, 0), 0x27);
    func_ov027_020b7e44(pool, BuildSlotImageParams(0, 2));
    menu->recordA = FindActiveRecordById(pool, 1);
    menu->recordB = FindActiveRecordById(pool, 2);
    menu->recordC = FindActiveRecordById(pool, 4);
    menu->recordD = FindActiveRecordById(pool, 3);
    menu->recordE = FindActiveRecordById(pool, 5);
    func_ov027_020b82a4(pool, menu->recordE, 7);
    menu->recordF = FindActiveRecordById(pool, 6);
    menu->recordG = FindActiveRecordById(pool, 7);
    func_ov027_020b97d8(widgets, FindWidgetById(widgets, 0xc), 2);
    func_ov027_020b97d8(widgets, FindWidgetById(widgets, 0xa), 2);
    func_ov027_020b9604(widgets, FindWidgetById(widgets, 0xb));
    menu->rowWidget = FindWidgetById(widgets, 0x38);
    menu->progressWidget = FindWidgetById(widgets, 0x39);
    menu->columnWidget = FindWidgetById(widgets, 0x3a);
    menu->listWidget = FindWidgetById(widgets, 0x3c);
    menu->scrollWidget = FindWidgetById(widgets, 0x3d);
    CreateContainerCells(widgets, menu->headerCells, 0x14, 6);

    pos = *GetWidgetPosition(widgets, FindWidgetById(widgets, 0xd));
    IndexedRecord_SetPair(widgets, menu->headerCells[2], &pos);
    pos.y += 0x10000;
    IndexedRecord_SetPair(widgets, menu->headerCells[3], &pos);
    pos.y += 0x10000;
    IndexedRecord_SetPair(widgets, menu->headerCells[4], &pos);
    pos.y += 0x10000;
    IndexedRecord_SetPair(widgets, menu->headerCells[5], &pos);
    pos.y += 0x20000;
    pos.x = 0x40000;
    IndexedRecord_SetPair(widgets, menu->headerCells[0], &pos);
    pos.y += 0x10000;
    IndexedRecord_SetPair(widgets, menu->headerCells[1], &pos);

    widget = FindWidgetById(widgets, 0x37);
    CreateContainerCells(widgets, menu->rowCellsA, 0x15, 7);
    func_ov027_020b9604(widgets, widget);
    menu->rowPos[0] = *GetWidgetPosition(widgets, widget);

    widget = FindWidgetById(widgets, 0x32);
    CreateContainerCells(widgets, menu->rowCellsB, 0x10, 7);
    func_ov027_020b9604(widgets, widget);
    menu->rowPos[1] = *GetWidgetPosition(widgets, widget);

    widget = FindWidgetById(widgets, 0x33);
    CreateContainerCells(widgets, menu->rowCellsC, 0x11, 7);
    func_ov027_020b9604(widgets, widget);
    menu->rowPos[2] = *GetWidgetPosition(widgets, widget);

    widget = FindWidgetById(widgets, 0x35);
    CreateContainerCells(widgets, menu->rowCellsD, 0x12, 7);
    func_ov027_020b9604(widgets, widget);
    menu->rowPos[3] = *GetWidgetPosition(widgets, widget);

    widget = FindWidgetById(widgets, 0x36);
    CreateContainerCells(widgets, menu->slotCells[0], 0x13, 0x1c);
    func_ov027_020b9604(widgets, widget);
    menu->rowPos[4] = *GetWidgetPosition(widgets, widget);
    menu->rowPos[4].x += 0x2000;

    for (; i < 7; i++) {
        IndexedRecords_SetFlag2(widgets, menu->rowCellsA[i], 0);
        IndexedRecords_SetFlag2(widgets, menu->rowCellsB[i], 0);
        IndexedRecords_SetFlag2(widgets, menu->rowCellsC[i], 0);
        IndexedRecords_SetFlag2(widgets, menu->rowCellsD[i], 0);
        IndexedRecords_SetFlag2(widgets, menu->slotCells[i][0], 0);
        IndexedRecords_SetFlag2(widgets, menu->slotCells[i][1], 0);
        IndexedRecords_SetFlag2(widgets, menu->slotCells[i][2], 0);
        IndexedRecords_SetFlag2(widgets, menu->slotCells[i][3], 0);
    }

    menu->playSeconds = data_0205fe0c->heartCount + (int)(((OS_GetTick() - GetCardThreadStartTick()) * 64) / 0x1ff6210);
    menu->munnyDigits = SetWidgetDigitDisplay(widgets, 4, 5, data_0205fe0c->munny);
    menu->timeDigits = func_ov039_020be378(widgets, 5, 6, menu->playSeconds);
    menu->listRows = 7;
    menu->listX = 0x30;
    menu->listWidth = 0xe8;
    func_ov034_020bdea4(menu->list, widgets, 8, 0x14, 0xc, 0, 0x10, 0, 0);
    menu->widgets = widgets;
    menu->recordPool = pool;
    frameA = data_ov073_020c4120;
    frameB = data_ov073_020c40c0;
    frameC = data_ov073_020c4100;

    screenBase = UpdateScreenWidgetLayer(0x19);
    menu->font = GetMenuFont10();
    menu->fontAlt = GetMenuFont08();
    LoadPackedFileView(menu->strings, sOv073_UiMenuStrLanguageStatusSZ_020c41b8, 0);
    ResetStatusHeaderText(menu);
    menu->titleText = func_ov027_020ba2c8(menu->strings, 0x25);
    menu->subtitleText = func_ov027_020ba2c8(menu->strings, 0x26);
    InitTextLayerAt(menu->textLayers[0], 5, screenBase, menu->font, &frameA);
    InitTextLayerAt(menu->textLayers[1], 5, screenBase, menu->font, &frameB);
    InitTextLayerAt(menu->textLayers[2], 5, screenBase, menu->font, &frameC);
    LoadStatusLabels(menu);

    menu->handlers[0].open = OpenStatusPageView;
    menu->handlers[0].update = func_ov073_020bff88;
    menu->handlers[0].draw = DrawStatusPanel;
    menu->handlers[0].close = HideStatusPageIcons;
    menu->handlers[0].page = menu->statText;
    menu->handlers[1].open = SetupStatusPageScroll;
    menu->handlers[1].update = HandleSlotListInput;
    menu->handlers[1].draw = func_ov073_020c0710;
    menu->handlers[1].close = HideStatusPageRows;
    menu->handlers[1].page = menu->recordList;
    menu->handlers[2].open = SetupStatusScreenScroll;
    menu->handlers[2].update = UpdateStatusListInput;
    menu->handlers[2].draw = func_ov073_020c0ed8;
    menu->handlers[2].close = HideStatusScreenElement;
    menu->handlers[2].page = menu->progressList;
    menu->handlers[3].open = SetupStatusPanelScroll;
    menu->handlers[3].update = UpdateStatusPanelInput;
    menu->handlers[3].draw = func_ov073_020c111c;
    menu->handlers[3].close = HideStatusPanelElement;
    menu->handlers[3].page = menu->columns;
    menu->handlers[4].open = InitStatusPanel;
    menu->handlers[4].update = UpdateStatusPanel;
    menu->handlers[4].draw = LoadStatusScreenResources;
    menu->handlers[4].close = CloseStatusScreen;
    menu->handlers[4].page = menu->details;

    menu->loaded = 2;
    menu->shown = 2;
    menu->mapLayout = AcquireMapLayout(FALSE, FALSE);
    menu->isCurrent = inSpecialMode;
    if (inSpecialMode || fromSpecialEntry
        || (data_0205fe0c->levelBonus == 0 && !IsGlobalPackedBitSet(0xa0b) && IsGlobalPackedBitSet(0x3520))) {
        value = TRUE;
    } else {
        value = FALSE;
    }
    menu->showExtra = value;
    ComputePlayerStats(data_0205fe0c, &stats, TRUE, 0);
    if (menu->isCurrent == 0) {
        RefreshStatusMenuData(data_0205fe0c, NULL);
    }
    menu->openTick = GetCardThreadStartTick();
    menu->isCurrent |= ((REG_POWCNT & 0x8000) >> 15) != 1;
    menu->heartCount = data_0205fe0c->heartCount;
    if (inSpecialMode || fromSpecialEntry || (GetFieldCad0() != 0 && GetMenuStackDepth() == 0)) {
        value = TRUE;
    } else {
        value = FALSE;
    }
    menu->eventsLocked = value;
    LoadSlotSubBgImage(0, 3, 0, value);

    handlers = &menu->handlers[menu->page];
    ResetStatusPageState(menu);
    handlers->open(menu, handlers->page);

    if (menu->showExtra) {
        widgets = GetMenuWidgetContainer();
        SetEntrySlotsVisible(widgets, FindWidgetById(widgets, 1), 0);
        SetEntrySlotsVisible(widgets, FindWidgetById(widgets, 2), 0);
    }
    if (((REG_POWCNT & 0x8000) >> 15) == 1 && !inSpecialMode) {
        RuntimeState_SetCondition(menu->showExtra == 0);
    }
    return 1;
}
