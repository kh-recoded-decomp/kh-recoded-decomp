#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

typedef struct Record Record;

typedef struct ListInitParams {
    u32 (*makeMessageKey)(u32 index);
    void (*refresh)(void);
    Record *record;
    int unk_0c;
    int uploadSlot;
    u8 selectionFlag;
    void *container;
    void *frameWidget;
    void *cursorWidget;
    int levelTier;
    int layerId;
    int cursorLayerId;
} ListInitParams;

typedef struct ListView {
    u8 pad_000[0x144];
    Record *record;
    u8 uploads[0x170 - 0x148];
    BOOL opened;
    BOOL restoreLayers;
} ListView;

typedef struct MenuSharedState {
    s8 page;
    u8 pad_001[0xb44 - 1];
    ListView list;
} MenuSharedState;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 flag;
} OverlaySelectionRecord;

typedef struct SelectionState {
    u8 pad_00[4];
    u8 values[6];
} SelectionState;

extern MenuSharedState *func_ov039_020bc630(void);
extern SelectionState *func_020505a8(void);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern void OS_WaitVBlankIntr_020049d0(void);
extern u32 MakeSharedMessageKey_020c13c4(u32 index);
extern void RefreshSharedUploadSlot_020c13f0(void);
extern int UpdateWidgetLayerDefault_020b9df0(void *uploads, int layerId);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern int GetPlayerLevelTier_020c1418(void);
extern void func_ov073_020c3ae0(ListView *list, ListInitParams *params);
extern void UploadListPalette_020c3f6c(ListView *list, BOOL immediate);
extern BOOL func_ov039_020bc0d4(void);
extern void SetEntrySlotsVisible_020b9580(void *container, void *element, BOOL visible);
extern void func_ov073_020c3fc8(ListView *list, u8 *values);

void ShowStatusRecordList_020c2b10(u8 *values)
{
    MenuSharedState *state = func_ov039_020bc630();
    ListView *list = &state->list;
    ListInitParams params;
    u32 layers;
    void *container;

    if (state->page != 4) {
        MI_CpuCopy8_01ff89a8(func_020505a8()->values, values, 6);
        return;
    }
    if (!list->opened) {
        layers = (REG_DB_DISPCNT & 0x1f00) >> 8;
        OS_WaitVBlankIntr_020049d0();
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1000;
        params.makeMessageKey = MakeSharedMessageKey_020c13c4;
        params.refresh = RefreshSharedUploadSlot_020c13f0;
        params.record = list->record;
        params.unk_0c = 0;
        params.uploadSlot = UpdateWidgetLayerDefault_020b9df0(list->uploads, 0x1a);
        params.selectionFlag = GetOverlaySelectionRecord_0204f768(0)->flag;
        params.container = func_ov039_020bc1cc();
        params.frameWidget = FindWidgetById_020b90a4(func_ov039_020bc1cc(), 0xe);
        params.cursorWidget = FindWidgetById_020b90a4(func_ov039_020bc1cc(), 0x3b);
        params.levelTier = GetPlayerLevelTier_020c1418();
        params.layerId = 0x1a;
        params.cursorLayerId = 0x1b;
        func_ov073_020c3ae0(list, &params);
        UploadListPalette_020c3f6c(list, TRUE);
        container = func_ov039_020bc1cc();
        SetEntrySlotsVisible_020b9580(container, params.frameWidget, func_ov039_020bc0d4() == FALSE);
        list->opened = TRUE;
        if (list->restoreLayers) {
            OS_WaitVBlankIntr_020049d0();
            REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (layers << 8);
        }
    }
    func_ov073_020c3fc8(list, values);
}
