#include "nitro/types.h"

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
    u8 pad_174[4];
    BOOL visible;
    u8 pad_17c[0x208 - 0x17c];
    u32 recordId;
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

extern MenuSharedState *func_ov039_020bc630(void);
extern void ReleaseListView_020c3c50(ListView *list);
extern void ReloadStatusRecord_020c29d8(ListView *list, u32 id);
extern u32 MakeSharedMessageKey_020c13c4(u32 index);
extern void RefreshSharedUploadSlot_020c13f0(void);
extern int UpdateWidgetLayerDefault_020b9df0(void *uploads, int layerId);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern int GetPlayerLevelTier_020c1418(void);
extern void func_ov073_020c3ae0(ListView *list, ListInitParams *params);
extern void UploadListPalette_020c3f6c(ListView *list, BOOL immediate);

void OpenStatusRecordList_020c2a04(u32 recordId)
{
    MenuSharedState *state = func_ov039_020bc630();
    ListView *list = &state->list;
    ListInitParams params;

    list->recordId = recordId;
    if (state->page == 4) {
        if (list->opened) {
            ReleaseListView_020c3c50(list);
        }
        ReloadStatusRecord_020c29d8(list, recordId);
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
        list->opened = TRUE;
        list->visible = TRUE;
    } else {
        ReloadStatusRecord_020c29d8(list, recordId);
    }
}
