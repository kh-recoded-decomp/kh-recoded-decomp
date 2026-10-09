#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc];
    u8 listLayer[0x9c];
    void *pageNodes[0x23];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    u8 pad_140[0x10];
    BOOL arrowsVisible;
    u8 pad_154[4];
    u16 pageMasks[7];
    u16 stepMasks[3];
    int extraUnlocked;
    int bonusUnlocked;
    u8 screenLayers[0x1c];
    u8 recordPool[0x10];
} Ov086Menu;

typedef struct {
    u32 offsets[8];
} PageNodeTable;

extern const PageNodeTable data_ov086_020c224c;

extern u8 *GetMenuWidgetContainer(void);
extern void *FindWidgetById(u8 *panel, int elementId);
extern void SetEntrySlotsVisible(u8 *panel, void *element, BOOL visible);
extern void ClearTileTableRowAndMarkDirty(void *table, int id);
extern BOOL IsRecordPageUnavailable(int page);
extern void ShowSecondaryPanelElementE(Ov086Menu *menu);
extern void RefreshSecondaryPanelList(Ov086Menu *menu);
extern void RefreshTertiaryPanel(Ov086Menu *menu);
extern void RefreshRecordGraphPanel(Ov086Menu *menu);
extern void RefreshSecondaryPanel(Ov086Menu *menu);
extern void SelectListNodeOrFirst(void *self, void *target);
extern void Text_UploadTileBuffer(void *surface);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8200(void *pool, void *record, s16 y);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b824c(void *pool, void *record, u16 x, u16 y);
extern void DrawRecordHintText(Ov086Menu *menu);

void RefreshRecordPageLayout(Ov086Menu *menu)
{
    int titleId = 9;
    u8 *panel = GetMenuWidgetContainer();
    PageNodeTable table = data_ov086_020c224c;

    ClearTileTableRowAndMarkDirty(menu->screenLayers, 0x1a);
    if (IsRecordPageUnavailable(menu->pageIndex)) {
        SetEntrySlotsVisible(panel, FindWidgetById(panel, titleId), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xb), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xf), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xd), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x10), FALSE);
        ShowSecondaryPanelElementE(menu);
    } else {
        int arrowId = 0xb;
        BOOL shown = TRUE;

        switch (menu->pageIndex) {
        case 3:
            SetEntrySlotsVisible(panel, FindWidgetById(panel, titleId), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xf), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, arrowId), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x10), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), shown);
            if (menu->arrowsVisible) {
                SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xd), shown);
            }
            RefreshSecondaryPanelList(menu);
            break;
        case 6:
            SetEntrySlotsVisible(panel, FindWidgetById(panel, titleId), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, arrowId), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xf), shown);
            if (menu->arrowsVisible) {
                SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x10), shown);
            }
            RefreshTertiaryPanel(menu);
            break;
        case 7:
            SetEntrySlotsVisible(panel, FindWidgetById(panel, titleId), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, arrowId), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xd), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xf), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x10), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, titleId), shown);
            if (menu->arrowsVisible) {
                SetEntrySlotsVisible(panel, FindWidgetById(panel, arrowId), shown);
            }
            RefreshRecordGraphPanel(menu);
            break;
        default:
            SetEntrySlotsVisible(panel, FindWidgetById(panel, titleId), shown);
            if (menu->arrowsVisible) {
                SetEntrySlotsVisible(panel, FindWidgetById(panel, arrowId), shown);
            }
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xf), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x10), FALSE);
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xd), FALSE);
            RefreshSecondaryPanel(menu);
            break;
        }
    }
    SelectListNodeOrFirst(menu->listLayer, menu->pageNodes[table.offsets[menu->pageIndex] + menu->stepCount]);
    Text_UploadTileBuffer(menu->listLayer);
    if (menu->stepCount != 0 && !IsRecordPageUnavailable(menu->pageIndex)) {
        void *record = FindActiveRecordById(menu->recordPool, 0x3ec);
        int page = menu->pageIndex;

        if (page == 7 || (page == 6 && menu->stepCount == 2)) {
            if ((page == 7 ? menu->bonusUnlocked : menu->extraUnlocked) != 0) {
                func_ov027_020b824c(menu->recordPool, record, 0x17, 9);
            }
        } else {
            u16 mask;
            int row;
            int col;

            if (page == 3 && menu->stepCount > 1) {
                mask = menu->stepMasks[menu->stepCount - 2];
            } else {
                mask = menu->pageMasks[page];
            }
            for (row = 0; row < 4; row++) {
                for (col = 0; col < 3; col++) {
                    if (mask & (1 << (col + row * 3))) {
                        func_ov027_020b8200(menu->recordPool, record, row * 9 + col * 2 + 5);
                        func_ov027_020b8230(menu->recordPool, record);
                    }
                }
            }
        }
    }
    DrawRecordHintText(menu);
}
