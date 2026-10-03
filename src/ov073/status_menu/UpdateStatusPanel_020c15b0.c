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
    int normalSequence;
    int highlightSequence;
} ListInitParams;

typedef struct StatusPanel {
    u8 pad_000[0x144];
    Record *record;
    u8 uploads[0x168 - 0x148];
    BOOL needsRedraw;
    BOOL uploadsReady;
    BOOL opened;
    u8 pad_174[0x184 - 0x174];
    void *screenBuffer;
    void *charBuffer;
    u8 pad_18c[0x1cc - 0x18c];
    u8 textLayer[0x200 - 0x1cc];
    int selectedRecord;
    int pendingFrames;
} StatusPanel;

typedef struct RecordEntry {
    u8 pad_00[0x2c];
    const u16 *name;
} RecordEntry;

typedef struct StatusMenu {
    s8 page;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0x11cc - 0x04];
    u8 strings[1];
} StatusMenu;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 flag;
} OverlaySelectionRecord;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern u32 MakeSharedMessageKey_020c13c4(u32 index);
extern void RefreshSharedUploadSlot_020c13f0(void);
extern int UpdateWidgetLayerDefault_020b9df0(void *uploads, int layerId);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern int GetPlayerLevelTier_020c1418(void);
extern void InitListView_020c3ae0(StatusPanel *list, ListInitParams *params);
extern void UploadListPalette_020c3f6c(StatusPanel *list, BOOL immediate);
extern BOOL func_ov039_020bc0d4(void);
extern void SetEntrySlotsVisible_020b9580(void *container, void *element, BOOL visible);
extern int func_ov073_020c3fa4(StatusPanel *panel);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern u16 *func_ov027_020ba2a8(void *table, int index);
extern void *func_ov039_020bc9ac(void);
extern RecordEntry *GetRecordSlotPair1Entry_02051ef4(int index);
extern void func_020016f0(void *layer, int x, int y, int color, u32 flags, const u16 *text, void *fallbackFont, int maxWidth);
extern void FlushBufferAndRunCallback_0200153c(void *context);

BOOL UpdateStatusPanel_020c15b0(StatusMenu *menu, StatusPanel *panel)
{
    ListInitParams params;
    void *container;
    int recordIndex;

    if (panel->pendingFrames == 1) {
        panel->pendingFrames = 0;
    }
    if (panel->needsRedraw) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(panel->screenBuffer);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(panel->charBuffer);
        panel->charBuffer = NULL;
        panel->screenBuffer = NULL;
        if (!panel->opened) {
            params.makeMessageKey = MakeSharedMessageKey_020c13c4;
            params.refresh = RefreshSharedUploadSlot_020c13f0;
            params.record = panel->record;
            params.unk_0c = 0;
            params.uploadSlot = UpdateWidgetLayerDefault_020b9df0(panel->uploads, 0x1a);
            params.selectionFlag = GetOverlaySelectionRecord_0204f768(0)->flag;
            params.container = func_ov039_020bc1cc();
            params.frameWidget = FindWidgetById_020b90a4(func_ov039_020bc1cc(), 0xe);
            params.cursorWidget = FindWidgetById_020b90a4(func_ov039_020bc1cc(), 0x3b);
            params.levelTier = GetPlayerLevelTier_020c1418();
            params.normalSequence = 0x1a;
            params.highlightSequence = 0x1b;
            InitListView_020c3ae0(panel, &params);
            UploadListPalette_020c3f6c(panel, TRUE);
            container = func_ov039_020bc1cc();
            SetEntrySlotsVisible_020b9580(container, params.frameWidget, func_ov039_020bc0d4() == FALSE);
            panel->opened = TRUE;
        }
        panel->uploadsReady = FALSE;
        panel->needsRedraw = FALSE;
        panel->pendingFrames--;
    }
    if ((menu->flags & 2) && (recordIndex = func_ov073_020c3fa4(panel)) != panel->selectedRecord) {
        CallVirtualHandlerSlot1_02001574(panel->textLayer, 0);
        if (recordIndex == -1) {
            func_020016f0(panel->textLayer, 4, 0, 2, 10, func_ov027_020ba2a8(menu->strings, 0x24),
                          func_ov039_020bc9ac(), 0xe4);
        } else {
            func_020016f0(panel->textLayer, 4, 0, 2, 10, GetRecordSlotPair1Entry_02051ef4(recordIndex)->name,
                          func_ov039_020bc9ac(), 0xe4);
        }
        FlushBufferAndRunCallback_0200153c(panel->textLayer);
        panel->selectedRecord = recordIndex;
    }
    if (panel->pendingFrames != 0) {
        return TRUE;
    }
    return FALSE;
}
