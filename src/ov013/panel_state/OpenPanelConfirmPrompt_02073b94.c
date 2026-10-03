#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct PanelState {
    u8 pad_00[0x9a];
    u8 mode : 2;
    u8 unk_9A_2 : 1;
    u8 isLocked : 1;
    u8 pad_9B[0x2bc - 0x9b];
    s32 resultState;
    u8 pad_2C0[0x6818 - 0x2c0];
    u8 panel[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern void func_ov013_0206f06c(void);
extern void func_ov013_02070a50(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern int func_ov002_020621c4(int textIndex, int unused);
extern void func_ov002_02061d58(int window, int x, int y, int palette, int width, int height, int text, int flags);
extern PanelObject *func_ov027_020b90a4(void *panel, int id);
extern void func_ov027_020b95e4(void *panel, PanelObject *object);
extern void func_ov027_020b96a0(void *panel, PanelObject *object, int mode);
extern void func_ov027_020b97b8(void *panel, PanelObject *object, int mode);
extern void SetEntrySlotsVisible_020b9580(void *panel, PanelObject *object, int visible);

void OpenPanelConfirmPrompt_02073b94(void) {
    PanelObject *object;
    u8 *panel;

    g_panelState_02074ce0->resultState = 0;
    g_panelState_02074ce0->isLocked = TRUE;
    func_ov013_0206f06c();
    PlaySoundEffect_0204d924(2, 3);
    func_ov013_02070a50();
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & ~3) | 2);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & ~3) | 3);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & ~3) | 1);
    *(vu16 *)0x0400100e = (u16)(*(vu16 *)0x0400100e & ~3);
    func_ov002_02061d58(1, 0x80, 0x41, 2, 6, 10, func_ov002_020621c4(0x6f, 0), 0);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 4);
    SetEntrySlotsVisible_020b9580(panel, object, 1);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 0);
    func_ov027_020b95e4(panel, object);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 4);
    func_ov027_020b97b8(panel, object, 0);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b95e4(panel, object);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b96a0(panel, object, 0);
}
