#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct ScrollList {
    s8 itemCount;
    s8 visibleCount;
    s8 rowInView;
    s8 scrollOffset;
    s8 cursor;
    u8 flags;
    u8 pad_06[2];
    int scrollPixels;
    int maxScrollPixels;
    int rowPixels;
    int rowHeight;
} ScrollList;

typedef struct SessionInfo {
    u32 unk_00;
    u16 checksum;
    u16 exitMode : 3;
    u16 unk_6_3 : 1;
    u16 resumed : 1;
    u16 rank : 3;
    u16 avatar : 5;
    u16 hasBonus : 1;
    s8 stage;
    s8 world;
    u8 progress;
    u8 pad_0B[0x10 - 0xb];
    s8 base;
    s8 offset;
    s8 slot;
    u8 linked;
} SessionInfo;

typedef struct PanelState {
    s8 slot;
    s8 phase;
    s8 world;
    s8 resultMode;
    s8 rowHeight;
    u8 pad_05[0x204 - 0x5];
    u32 rolls[21];
    u8 slotPending[0x2cc - 0x258];
    s32 scrollOffset;
    u8 pad_2D0[0x2ec - 0x2d0];
    ScrollList list;
    u8 pad_304[0x39c - 0x304];
    u8 manager[0x6818 - 0x39c];
    u8 panel[0xd258 - 0x6818];
    s8 lastSlot;
    u8 flags;
    u8 pad_D25A[2];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern SessionInfo data_0206085c;
extern void func_ov013_02074498(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int DispatchContextCommand_02066c78(u32 command, int value, int extra, void *buffer);
extern void QueryPanelSlotStates_02071590(void);
extern void func_ov002_020629a8(void);
extern u32 IsPanelBusy_02062c6c(void);
extern int SetSelectionIfChanged_0204d73c(int selection);
extern void func_ov013_0206df40(int index);
extern void func_ov013_0206caa4(void);
extern void func_ov013_0206da20(void);
extern void func_ov013_0206d078(void);
extern void func_ov027_020b9874(void *panel, int flag);
extern void func_ov027_020b984c(void *panel, int flag);
extern void InitScrollList_0206314c(ScrollList *list, int itemCount, int visibleCount, int rowHeight);
extern void func_ov013_02070a18(void);
extern void SetScrollListPosition_02063280(ScrollList *list, int scrollOffset, int rowInView);
extern PanelObject *func_ov027_020b90a4(void *panel, int id);
extern void SetEntrySlotsVisible_020b9580(void *panel, PanelObject *object, int visible);
extern u32 func_0202a9d0(u32 range);
extern void InitMenuCursorState(void (*callback)(void));
extern void func_ov013_020716e4(int mode);
extern void SetPanelPhase_0207174c(s8 phase);

void InitPanelScene_0206c480(void) {
    int i;

    AcquireRecordSlot_02051d3c(9, 1);
    g_panelState_02074ce0 = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(PanelState));
    func_01ff8830(g_panelState_02074ce0, 0, sizeof(PanelState));
    g_panelState_02074ce0->slot = -1;
    g_panelState_02074ce0->lastSlot = -1;
    g_panelState_02074ce0->phase = 0;
    g_panelState_02074ce0->world = DispatchContextCommand_02066c78(1, 0, 0, NULL);
    g_panelState_02074ce0->world += (s8)((g_panelState_02074ce0->world + (g_panelState_02074ce0->world + 1) / 10 + 1) / 10);
    QueryPanelSlotStates_02071590();
    func_ov002_020629a8();
    if (IsPanelBusy_02062c6c()) {
        func_ov013_0206caa4();
    } else {
        switch (data_0206085c.exitMode) {
        case 0:
            if (!data_0206085c.resumed) {
                SetSelectionIfChanged_0204d73c(1);
                func_ov013_0206caa4();
            } else {
                func_ov013_0206df40(data_0206085c.offset + data_0206085c.base);
            }
            break;
        case 2:
        case 4:
            func_ov013_0206caa4();
            SetSelectionIfChanged_0204d73c(1);
            break;
        case 1:
            if (data_0206085c.slot == 7) {
                func_ov013_0206df40(data_0206085c.offset + data_0206085c.base);
            } else {
                func_ov013_0206da20();
            }
            break;
        case 3:
            func_ov013_0206caa4();
            break;
        }
    }
    func_ov013_0206d078();
    func_ov027_020b9874(g_panelState_02074ce0->panel, 1);
    func_ov027_020b9874(g_panelState_02074ce0->manager, 1);
    func_ov027_020b984c(g_panelState_02074ce0->panel, 1);
    InitScrollList_0206314c(&g_panelState_02074ce0->list, g_panelState_02074ce0->world, 6, g_panelState_02074ce0->rowHeight);
    func_ov013_02070a18();
    if (!IsPanelBusy_02062c6c()) {
        SetScrollListPosition_02063280(&g_panelState_02074ce0->list, data_0206085c.offset, data_0206085c.base);
        g_panelState_02074ce0->scrollOffset = -g_panelState_02074ce0->list.scrollPixels;
    }
    if (g_panelState_02074ce0->list.scrollOffset == 0) {
        SetEntrySlotsVisible_020b9580(g_panelState_02074ce0->panel, func_ov027_020b90a4(g_panelState_02074ce0->panel, 2), 0);
    }
    if (g_panelState_02074ce0->list.scrollOffset >= g_panelState_02074ce0->list.itemCount - g_panelState_02074ce0->list.visibleCount) {
        SetEntrySlotsVisible_020b9580(g_panelState_02074ce0->panel, func_ov027_020b90a4(g_panelState_02074ce0->panel, 3), 0);
    }
    if (g_panelState_02074ce0->slotPending[g_panelState_02074ce0->list.cursor] == 1) {
        g_panelState_02074ce0->slotPending[g_panelState_02074ce0->list.cursor] = 2;
    }
    for (i = 0; i < 21; i++) {
        g_panelState_02074ce0->rolls[i] = func_0202a9d0(2) + 1;
    }
    InitMenuCursorState(func_ov013_02074498);
    func_ov013_020716e4(0);
    SetPanelPhase_0207174c(0);
}
