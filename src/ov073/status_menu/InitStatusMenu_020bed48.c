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
extern const ObjConfig data_ov073_020c40c0;
extern const TextFrame data_ov073_020c4100;
extern const TextFrame data_ov073_020c40a0;
extern const TextFrame data_ov073_020c40e0;
extern const char data_ov073_020c4198[];

extern int func_ov039_020bc914(void);
extern int func_ov039_020bc7f8(void);
extern void func_01ff8830(void *dest, int value, int size);
extern int func_02025658(void);
extern u8 *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern BOOL AcquireRecordManager_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void func_0200672c(int mode);
extern void *G2S_GetBG1CharPtr_02007100(void);
extern void func_01ff8740(int value, void *dest, int size);
extern void *func_ov039_020bc1a4(void);
extern void *func_ov039_020bc1cc(void);
extern u32 BuildSlotImageParams_020bc220(int slot, unsigned int low);
extern void InitObjManagerAndMark_020b9060(void *obj, void *config);
extern void func_ov027_020b9078(void *widgets, u32 params);
extern void func_ov027_020b8f98(void *widgets, u32 params, int count);
extern void func_ov027_020b7e24(void *pool, u32 params);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void func_ov027_020b8284(void *pool, void *record, int mode);
extern void *FindWidgetById_020b90a4(void *root, int id);
extern void func_ov027_020b97b8(void *widgets, void *widget, int mode);
extern void func_ov027_020b95e4(void *widgets, void *widget);
extern void CreateContainerCells_020bfed0(void *container, s16 *cells, int cellId, int count);
extern CellPos *func_ov027_020b91a8(void *widgets, void *widget);
extern void func_0204f13c(void *widgets, int index, CellPos *pos);
extern void func_0204f378(void *widgets, int index, int value);
extern u64 OS_GetTick_02003fd4(void);
extern s64 GetCardThreadStartTick_0202726c(void);
extern s16 SetWidgetDigitDisplay_020be234(void *cells, int widgetId, int key, u32 value);
extern s16 func_ov039_020be358(void *cells, int widgetId, int key, u32 value);
extern void func_ov034_020bde84(void *list, void *widgets, int x, int y, int rows, int a, int b, int c, int d);
extern u16 *UpdateScreenWidgetLayer_020bc1e4(int widget);
extern void *func_ov039_020bc994(void);
extern void *func_ov039_020bc97c(void);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern void ResetStatusHeaderText_020beb7c(StatusMenu *menu);
extern void *func_ov027_020ba2a8(void *strings, int index);
extern BOOL InitTextLayerAt_020014b0(void *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void LoadStatusLabels_020bfc58(StatusMenu *menu);
extern int *AcquireMapLayout_020506dc(BOOL reload, BOOL discard);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void ComputePlayerStats_02050b30(SaveData *save, PlayerStats *out, BOOL recompute, int scale);
extern void RefreshStatusMenuData_020c1eb4(SaveData *save, void *preview);
extern int GetFieldCad0_020bcb00(void);
extern int func_ov039_020bc810(void);
extern void StartCurrentAreaEvents_020bc55c(int a, int b, int c, u16 d);
extern void ResetStatusPageState_020beaa0(StatusMenu *menu);
extern void SetEntrySlotsVisible_020b9580(void *widgets, void *widget, int visible);
extern void func_ov039_020bc03c(BOOL flag);

extern void OpenStatusPageView_020bfefc(StatusMenu *menu, void *page);
extern void FSi_CloseFileCommand_020bff68(StatusMenu *menu, void *page);
extern void DrawStatusPanel_020bff6c(StatusMenu *menu, void *page);
extern void HideStatusPageIcons_020c01e4(StatusMenu *menu, void *page);
extern void SetupStatusPageScroll_020c0220(StatusMenu *menu, void *page);
extern void HandleSlotListInput_020c032c(StatusMenu *menu, void *page);
extern void func_ov073_020c06f0(StatusMenu *menu, void *page);
extern void HideStatusPageRows_020c0d88(StatusMenu *menu, void *page);
extern void SetupStatusScreenScroll_020c0dec(StatusMenu *menu, void *page);
extern void UpdateStatusListInput_020c0e38(StatusMenu *menu, void *page);
extern void func_ov073_020c0eb8(StatusMenu *menu, void *page);
extern void HideStatusScreenElement_020c1024(StatusMenu *menu, void *page);
extern void SetupStatusPanelScroll_020c1040(StatusMenu *menu, void *page);
extern void func_ov073_020c1088(StatusMenu *menu, void *page);
extern void func_ov073_020c10fc(StatusMenu *menu, void *page);
extern void HideStatusPanelElement_020c1230(StatusMenu *menu, void *page);
extern void InitStatusPanel_020c1488(StatusMenu *menu, void *page);
extern void UpdateStatusPanel_020c15b0(StatusMenu *menu, void *page);
extern void func_ov073_020c173c(StatusMenu *menu, void *page);
extern void CloseStatusScreen_020c1864(StatusMenu *menu, void *page);

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)
#define REG_DB_BG2OFS (*(vu32 *)0x04001018)
#define REG_POWCNT (*(vu16 *)0x04000304)

int InitStatusMenu_020bed48(StatusMenu *menu)
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

    inSpecialMode = func_ov039_020bc914() == 3;
    fromSpecialEntry = func_ov039_020bc7f8() == 0x4100;
    func_01ff8830(menu, 0, sizeof(StatusMenu));
    menu->wirelessMode = func_ov039_020bc914() == 3 && func_02025658() == 1;
    i = 0;
    menu->selection = GetOverlaySelectionRecord(0)[0x10];
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(3, 1);
    func_0200672c(0);

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
    func_01ff8740(0, G2S_GetBG1CharPtr_02007100(), 0x20);

    pool = func_ov039_020bc1a4();
    widgets = func_ov039_020bc1cc();
    config = data_ov073_020c40c0;
    config.words[0] = BuildSlotImageParams_020bc220(0, 1);
    InitObjManagerAndMark_020b9060(widgets, &config);
    func_ov027_020b9078(widgets, BuildSlotImageParams_020bc220(1, 2));
    func_ov027_020b8f98(widgets, BuildSlotImageParams_020bc220(0, 0), 0x27);
    func_ov027_020b7e24(pool, BuildSlotImageParams_020bc220(0, 2));
    menu->recordA = FindActiveRecordById_020b8184(pool, 1);
    menu->recordB = FindActiveRecordById_020b8184(pool, 2);
    menu->recordC = FindActiveRecordById_020b8184(pool, 4);
    menu->recordD = FindActiveRecordById_020b8184(pool, 3);
    menu->recordE = FindActiveRecordById_020b8184(pool, 5);
    func_ov027_020b8284(pool, menu->recordE, 7);
    menu->recordF = FindActiveRecordById_020b8184(pool, 6);
    menu->recordG = FindActiveRecordById_020b8184(pool, 7);
    func_ov027_020b97b8(widgets, FindWidgetById_020b90a4(widgets, 0xc), 2);
    func_ov027_020b97b8(widgets, FindWidgetById_020b90a4(widgets, 0xa), 2);
    func_ov027_020b95e4(widgets, FindWidgetById_020b90a4(widgets, 0xb));
    menu->rowWidget = FindWidgetById_020b90a4(widgets, 0x38);
    menu->progressWidget = FindWidgetById_020b90a4(widgets, 0x39);
    menu->columnWidget = FindWidgetById_020b90a4(widgets, 0x3a);
    menu->listWidget = FindWidgetById_020b90a4(widgets, 0x3c);
    menu->scrollWidget = FindWidgetById_020b90a4(widgets, 0x3d);
    CreateContainerCells_020bfed0(widgets, menu->headerCells, 0x14, 6);

    pos = *func_ov027_020b91a8(widgets, FindWidgetById_020b90a4(widgets, 0xd));
    func_0204f13c(widgets, menu->headerCells[2], &pos);
    pos.y += 0x10000;
    func_0204f13c(widgets, menu->headerCells[3], &pos);
    pos.y += 0x10000;
    func_0204f13c(widgets, menu->headerCells[4], &pos);
    pos.y += 0x10000;
    func_0204f13c(widgets, menu->headerCells[5], &pos);
    pos.y += 0x20000;
    pos.x = 0x40000;
    func_0204f13c(widgets, menu->headerCells[0], &pos);
    pos.y += 0x10000;
    func_0204f13c(widgets, menu->headerCells[1], &pos);

    widget = FindWidgetById_020b90a4(widgets, 0x37);
    CreateContainerCells_020bfed0(widgets, menu->rowCellsA, 0x15, 7);
    func_ov027_020b95e4(widgets, widget);
    menu->rowPos[0] = *func_ov027_020b91a8(widgets, widget);

    widget = FindWidgetById_020b90a4(widgets, 0x32);
    CreateContainerCells_020bfed0(widgets, menu->rowCellsB, 0x10, 7);
    func_ov027_020b95e4(widgets, widget);
    menu->rowPos[1] = *func_ov027_020b91a8(widgets, widget);

    widget = FindWidgetById_020b90a4(widgets, 0x33);
    CreateContainerCells_020bfed0(widgets, menu->rowCellsC, 0x11, 7);
    func_ov027_020b95e4(widgets, widget);
    menu->rowPos[2] = *func_ov027_020b91a8(widgets, widget);

    widget = FindWidgetById_020b90a4(widgets, 0x35);
    CreateContainerCells_020bfed0(widgets, menu->rowCellsD, 0x12, 7);
    func_ov027_020b95e4(widgets, widget);
    menu->rowPos[3] = *func_ov027_020b91a8(widgets, widget);

    widget = FindWidgetById_020b90a4(widgets, 0x36);
    CreateContainerCells_020bfed0(widgets, menu->slotCells[0], 0x13, 0x1c);
    func_ov027_020b95e4(widgets, widget);
    menu->rowPos[4] = *func_ov027_020b91a8(widgets, widget);
    menu->rowPos[4].x += 0x2000;

    for (; i < 7; i++) {
        func_0204f378(widgets, menu->rowCellsA[i], 0);
        func_0204f378(widgets, menu->rowCellsB[i], 0);
        func_0204f378(widgets, menu->rowCellsC[i], 0);
        func_0204f378(widgets, menu->rowCellsD[i], 0);
        func_0204f378(widgets, menu->slotCells[i][0], 0);
        func_0204f378(widgets, menu->slotCells[i][1], 0);
        func_0204f378(widgets, menu->slotCells[i][2], 0);
        func_0204f378(widgets, menu->slotCells[i][3], 0);
    }

    menu->playSeconds = data_0205fe0c->heartCount + (int)(((OS_GetTick_02003fd4() - GetCardThreadStartTick_0202726c()) * 64) / 0x1ff6210);
    menu->munnyDigits = SetWidgetDigitDisplay_020be234(widgets, 4, 5, data_0205fe0c->munny);
    menu->timeDigits = func_ov039_020be358(widgets, 5, 6, menu->playSeconds);
    menu->listRows = 7;
    menu->listX = 0x30;
    menu->listWidth = 0xe8;
    func_ov034_020bde84(menu->list, widgets, 8, 0x14, 0xc, 0, 0x10, 0, 0);
    menu->widgets = widgets;
    menu->recordPool = pool;
    frameA = data_ov073_020c4100;
    frameB = data_ov073_020c40a0;
    frameC = data_ov073_020c40e0;

    screenBase = UpdateScreenWidgetLayer_020bc1e4(0x19);
    menu->font = func_ov039_020bc994();
    menu->fontAlt = func_ov039_020bc97c();
    LoadPackedFileView_020ba25c(menu->strings, data_ov073_020c4198, 0);
    ResetStatusHeaderText_020beb7c(menu);
    menu->titleText = func_ov027_020ba2a8(menu->strings, 0x25);
    menu->subtitleText = func_ov027_020ba2a8(menu->strings, 0x26);
    InitTextLayerAt_020014b0(menu->textLayers[0], 5, screenBase, menu->font, &frameA);
    InitTextLayerAt_020014b0(menu->textLayers[1], 5, screenBase, menu->font, &frameB);
    InitTextLayerAt_020014b0(menu->textLayers[2], 5, screenBase, menu->font, &frameC);
    LoadStatusLabels_020bfc58(menu);

    menu->handlers[0].open = OpenStatusPageView_020bfefc;
    menu->handlers[0].update = FSi_CloseFileCommand_020bff68;
    menu->handlers[0].draw = DrawStatusPanel_020bff6c;
    menu->handlers[0].close = HideStatusPageIcons_020c01e4;
    menu->handlers[0].page = menu->statText;
    menu->handlers[1].open = SetupStatusPageScroll_020c0220;
    menu->handlers[1].update = HandleSlotListInput_020c032c;
    menu->handlers[1].draw = func_ov073_020c06f0;
    menu->handlers[1].close = HideStatusPageRows_020c0d88;
    menu->handlers[1].page = menu->recordList;
    menu->handlers[2].open = SetupStatusScreenScroll_020c0dec;
    menu->handlers[2].update = UpdateStatusListInput_020c0e38;
    menu->handlers[2].draw = func_ov073_020c0eb8;
    menu->handlers[2].close = HideStatusScreenElement_020c1024;
    menu->handlers[2].page = menu->progressList;
    menu->handlers[3].open = SetupStatusPanelScroll_020c1040;
    menu->handlers[3].update = func_ov073_020c1088;
    menu->handlers[3].draw = func_ov073_020c10fc;
    menu->handlers[3].close = HideStatusPanelElement_020c1230;
    menu->handlers[3].page = menu->columns;
    menu->handlers[4].open = InitStatusPanel_020c1488;
    menu->handlers[4].update = UpdateStatusPanel_020c15b0;
    menu->handlers[4].draw = func_ov073_020c173c;
    menu->handlers[4].close = CloseStatusScreen_020c1864;
    menu->handlers[4].page = menu->details;

    menu->loaded = 2;
    menu->shown = 2;
    menu->mapLayout = AcquireMapLayout_020506dc(FALSE, FALSE);
    menu->isCurrent = inSpecialMode;
    if (inSpecialMode || fromSpecialEntry
        || (data_0205fe0c->levelBonus == 0 && !IsGlobalPackedBitSet_02027304(0xa0b) && IsGlobalPackedBitSet_02027304(0x3520))) {
        value = TRUE;
    } else {
        value = FALSE;
    }
    menu->showExtra = value;
    ComputePlayerStats_02050b30(data_0205fe0c, &stats, TRUE, 0);
    if (menu->isCurrent == 0) {
        RefreshStatusMenuData_020c1eb4(data_0205fe0c, NULL);
    }
    menu->openTick = GetCardThreadStartTick_0202726c();
    menu->isCurrent |= ((REG_POWCNT & 0x8000) >> 15) != 1;
    menu->heartCount = data_0205fe0c->heartCount;
    if (inSpecialMode || fromSpecialEntry || (GetFieldCad0_020bcb00() != 0 && func_ov039_020bc810() == 0)) {
        value = TRUE;
    } else {
        value = FALSE;
    }
    menu->eventsLocked = value;
    StartCurrentAreaEvents_020bc55c(0, 3, 0, value);

    handlers = &menu->handlers[menu->page];
    ResetStatusPageState_020beaa0(menu);
    handlers->open(menu, handlers->page);

    if (menu->showExtra) {
        widgets = func_ov039_020bc1cc();
        SetEntrySlotsVisible_020b9580(widgets, FindWidgetById_020b90a4(widgets, 1), 0);
        SetEntrySlotsVisible_020b9580(widgets, FindWidgetById_020b90a4(widgets, 2), 0);
    }
    if (((REG_POWCNT & 0x8000) >> 15) == 1 && !inSpecialMode) {
        func_ov039_020bc03c(menu->showExtra == 0);
    }
    return 1;
}
