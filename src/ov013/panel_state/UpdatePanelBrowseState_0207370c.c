#include "nitro/types.h"

typedef struct ScrollList {
    s32 count;
    s8 index;
    u8 pad_05[3];
    s32 scroll;
} ScrollList;

typedef struct PanelState {
    u8 pad_00[0x3];
    s8 resultMode;
    u8 pad_04[0x98 - 0x4];
    u8 unk_98_0 : 6;
    u8 playsCue : 1;
    u8 pad_99[0x2bc - 0x99];
    s32 resultState;
    u8 pad_2C0[0x2cc - 0x2c0];
    s32 scrollOffset;
    u8 pad_2D0[0x2ec - 0x2d0];
    ScrollList list;
    u8 pad_2F8[0x39c - 0x2f8];
    u8 panel[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern u32 func_ov002_0206655c(void);
extern BOOL IsButtonXPressed_020632e4(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void StartPanelFadeOut(int mode);
extern u16 *func_ov002_02062000(void);
extern void func_ov027_020b8ca8(void *panel, int value);
extern u32 ScrollListKeys_020631b4(u32 keys, ScrollList *list);
extern void func_ov013_020704a0(void);
extern void func_ov013_0206fbbc(void);
extern void RefreshProgressCaption_0206f06c(void);
extern void func_ov013_020716e4(int mode);
extern void func_ov013_0206f978(int mode);

void UpdatePanelBrowseState_0207370c(void) {
    switch (g_panelState_02074ce0->resultState) {
    case 0:
        if (func_ov002_0206655c()) {
            if (g_panelState_02074ce0->playsCue) {
                PlaySoundEffect_0204d924(2, 0xb);
            }
            g_panelState_02074ce0->resultState = 10;
        }
        break;
    case 10:
        if (IsButtonXPressed_020632e4()) {
            PlaySoundEffect_0204d924(2, 3);
            StartPanelFadeOut(3);
            g_panelState_02074ce0->resultState = 60;
            break;
        }
        func_ov027_020b8ca8(g_panelState_02074ce0->panel, *func_ov002_02062000());
        switch (g_panelState_02074ce0->resultMode) {
        case 1:
            StartPanelFadeOut(3);
            g_panelState_02074ce0->resultState = 50;
            break;
        case 2:
            StartPanelFadeOut(3);
            g_panelState_02074ce0->resultState = 40;
            break;
        }
        break;
    case 40:
        if (func_ov002_0206655c()) {
            func_ov013_0206f978(2);
        }
        break;
    case 50:
        if (func_ov002_0206655c()) {
            ScrollListKeys_020631b4(0x80, &g_panelState_02074ce0->list);
            g_panelState_02074ce0->scrollOffset = -g_panelState_02074ce0->list.scroll;
            func_ov013_020704a0();
            func_ov013_0206fbbc();
            RefreshProgressCaption_0206f06c();
            if ((g_panelState_02074ce0->list.index + 1) % 10 != 0) {
                func_ov013_020716e4(6);
            } else {
                func_ov013_0206f978(0);
            }
        }
        break;
    case 60:
        if (func_ov002_0206655c()) {
            func_ov013_0206f978(1);
        }
        break;
    }
}
