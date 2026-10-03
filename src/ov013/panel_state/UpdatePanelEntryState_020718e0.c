#include "nitro/types.h"

typedef struct ScrollList {
    s32 count;
    s8 index;
    u8 pad_05[3];
    s32 scroll;
} ScrollList;

typedef struct PanelState {
    u8 pad_00[0x2bc];
    s32 resultState;
    u8 pad_2C0[0x2cc - 0x2c0];
    s32 scrollOffset;
    u8 pad_2D0[0x2ec - 0x2d0];
    ScrollList list;
    u8 pad_2F8[0xd259 - 0x2f8];
    u8 showSelection : 1;
} PanelState;

typedef struct ProgressCursor {
    u8 pad_00[0x10];
    s8 base;
    s8 offset;
} ProgressCursor;

extern PanelState *g_panelState_02074ce0;
extern ProgressCursor data_0206085c;
extern void func_ov013_0206cfd8(void);
extern void func_ov013_020704a0(void);
extern void func_ov013_0206e574(void);
extern void RebuildPanelSelection_020712e8(void);
extern void RecordPanelClear_02070f50(int index);
extern void func_ov013_0206fbbc(void);
extern void RefreshProgressCaption_0206f06c(void);
extern void func_ov013_020716e4(int mode);
extern void func_ov002_02062014(int value);
extern void func_ov002_020664e4(int mode);
extern u32 func_ov002_0206655c(void);
extern int DispatchContextCommand_02066c78(u32 command, int value, int extra, void *buffer);
extern u32 ScrollListKeys_020631b4(u32 keys, ScrollList *list);

void UpdatePanelEntryState_020718e0(void) {
    switch (g_panelState_02074ce0->resultState) {
    case 0:
        func_ov013_0206cfd8();
        func_ov013_020704a0();
        func_ov013_0206e574();
        if ((g_panelState_02074ce0->list.index + 1) % 10 != 0) {
            RebuildPanelSelection_020712e8();
            g_panelState_02074ce0->showSelection = 1;
        }
        func_ov002_02062014(1);
        g_panelState_02074ce0->resultState = 10;
        break;
    case 10:
        func_ov002_020664e4(3);
        g_panelState_02074ce0->resultState = 20;
        break;
    case 20:
        if (func_ov002_0206655c()) {
            if (DispatchContextCommand_02066c78(0xd, 0, 0, NULL) == 0) {
                func_ov013_020716e4(0xb);
            } else {
                func_ov013_020716e4(1);
            }
        }
        break;
    case 50:
        func_ov002_02062014(1);
        func_ov013_020716e4(6);
        break;
    case 60:
        func_ov002_02062014(1);
        func_ov013_020716e4(7);
        break;
    case 70:
        func_ov002_02062014(1);
        RecordPanelClear_02070f50(data_0206085c.offset + data_0206085c.base);
        ScrollListKeys_020631b4(0x80, &g_panelState_02074ce0->list);
        g_panelState_02074ce0->scrollOffset = -g_panelState_02074ce0->list.scroll;
        func_ov013_020704a0();
        func_ov013_0206fbbc();
        RefreshProgressCaption_0206f06c();
        func_ov013_020716e4(6);
        break;
    }
}
