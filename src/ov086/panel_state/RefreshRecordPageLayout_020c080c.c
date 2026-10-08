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

extern const PageNodeTable data_ov086_020c222c;

extern u8 *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(u8 *panel, int elementId);
extern void func_ov027_020b9580(u8 *panel, void *element, BOOL visible);
extern void ClearTileTableRowAndMarkDirty_020b9d18(void *table, int id);
extern BOOL IsRecordPageUnavailable_020c2080(int page);
extern void ShowSecondaryPanelElementE_020c0320(Ov086Menu *menu);
extern void RefreshSecondaryPanelList_020c0128(Ov086Menu *menu);
extern void RefreshTertiaryPanel_020c042c(Ov086Menu *menu);
extern void RefreshRecordGraphPanel_020c0628(Ov086Menu *menu);
extern void RefreshSecondaryPanel_020bff24(Ov086Menu *menu);
extern void SelectListNodeOrFirst_020019b8(void *self, void *target);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void func_ov027_020b81e0(void *pool, void *record, s16 y);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov027_020b822c(void *pool, void *record, u16 x, u16 y);
extern void DrawRecordHintText_020bebe8(Ov086Menu *menu);

void RefreshRecordPageLayout_020c080c(Ov086Menu *menu)
{
    int titleId = 9;
    u8 *panel = func_ov039_020bc1cc();
    PageNodeTable table = data_ov086_020c222c;

    ClearTileTableRowAndMarkDirty_020b9d18(menu->screenLayers, 0x1a);
    if (IsRecordPageUnavailable_020c2080(menu->pageIndex)) {
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, titleId), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xb), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xf), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xd), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x10), FALSE);
        ShowSecondaryPanelElementE_020c0320(menu);
    } else {
        int arrowId = 0xb;
        BOOL shown = TRUE;

        switch (menu->pageIndex) {
        case 3:
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, titleId), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xf), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, arrowId), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x10), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), shown);
            if (menu->arrowsVisible) {
                func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xd), shown);
            }
            RefreshSecondaryPanelList_020c0128(menu);
            break;
        case 6:
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, titleId), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, arrowId), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xf), shown);
            if (menu->arrowsVisible) {
                func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x10), shown);
            }
            RefreshTertiaryPanel_020c042c(menu);
            break;
        case 7:
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, titleId), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, arrowId), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xd), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xf), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x10), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, titleId), shown);
            if (menu->arrowsVisible) {
                func_ov027_020b9580(panel, func_ov027_020b90a4(panel, arrowId), shown);
            }
            RefreshRecordGraphPanel_020c0628(menu);
            break;
        default:
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, titleId), shown);
            if (menu->arrowsVisible) {
                func_ov027_020b9580(panel, func_ov027_020b90a4(panel, arrowId), shown);
            }
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xf), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x10), FALSE);
            func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xd), FALSE);
            RefreshSecondaryPanel_020bff24(menu);
            break;
        }
    }
    SelectListNodeOrFirst_020019b8(menu->listLayer, menu->pageNodes[table.offsets[menu->pageIndex] + menu->stepCount]);
    Text_UploadTileBuffer_02001520(menu->listLayer);
    if (menu->stepCount != 0 && !IsRecordPageUnavailable_020c2080(menu->pageIndex)) {
        void *record = FindActiveRecordById_020b8184(menu->recordPool, 0x3ec);
        int page = menu->pageIndex;

        if (page == 7 || (page == 6 && menu->stepCount == 2)) {
            if ((page == 7 ? menu->bonusUnlocked : menu->extraUnlocked) != 0) {
                func_ov027_020b822c(menu->recordPool, record, 0x17, 9);
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
                        func_ov027_020b81e0(menu->recordPool, record, row * 9 + col * 2 + 5);
                        TagTracker_InvokeCallback_020b8210(menu->recordPool, record);
                    }
                }
            }
        }
    }
    DrawRecordHintText_020bebe8(menu);
}
