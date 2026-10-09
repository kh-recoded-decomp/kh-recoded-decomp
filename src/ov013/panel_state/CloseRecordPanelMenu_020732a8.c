#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct PanelState {
    u8 pad_00[0x3];
    s8 resultMode;
    u8 pad_04[0x2bc - 0x4];
    s32 resultState;
    u8 pad_2C0[0x6818 - 0x2c0];
    u8 panel[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern void func_ov002_0206203c(int selector);
extern void func_ov013_0206da20(void);
extern void func_ov013_0206eb18(void);
extern BOOL func_02029f58(void);
extern void func_ov013_0206f06c(void);
extern void StartPanelFadeIn(int mode);
extern int GetCachedSoundParam_0204d720(void);
extern int func_0204d8b8(int arg0, int arg1);
extern PanelObject *func_ov027_020b90a4(void *panel, int id);
extern void func_ov027_020b95e4(void *panel, PanelObject *object);
extern void func_ov027_020b96a0(void *panel, PanelObject *object, int mode);
extern void SetEntrySlotsVisible_020b9580(void *panel, PanelObject *object, int visible);

void CloseRecordPanelMenu_020732a8(void) {
    PanelObject *object;
    u8 *panel;
    u32 mode;

    mode = 0;
    g_panelState_02074ce0->resultState = 0;
    func_ov013_0206da20();
    func_ov002_0206203c(-1);
    func_ov013_0206eb18();
    func_ov013_0206f06c();
    if (func_02029f58()) {
        mode = 2;
    }
    object = func_ov027_020b90a4(g_panelState_02074ce0->panel, 0);
    func_ov027_020b95e4(g_panelState_02074ce0->panel, object);
    object = func_ov027_020b90a4(g_panelState_02074ce0->panel, 2);
    func_ov027_020b95e4(g_panelState_02074ce0->panel, object);
    object = func_ov027_020b90a4(g_panelState_02074ce0->panel, 3);
    func_ov027_020b95e4(g_panelState_02074ce0->panel, object);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b95e4(panel, object);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b96a0(panel, object, 0);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 6);
    SetEntrySlotsVisible_020b9580(panel, object, 0);
    StartPanelFadeIn(mode | 1);
    if (GetCachedSoundParam_0204d720() != 22) {
        func_0204d8b8(22, 15);
    }
}
