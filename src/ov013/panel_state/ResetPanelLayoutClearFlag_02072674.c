#include "nitro/types.h"

typedef struct PanelObject PanelObject;

typedef struct PanelState {
    u8 pad_00[0x9a];
    u8 mode : 2;
    u8 unk_9A_2 : 1;
    u8 isLocked : 1;
    u8 pad_9B[0x6818 - 0x9b];
    u8 panel[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern void func_ov002_020620fc(int selector);
extern void func_ov013_02070aa0(void);
extern void func_ov013_0206f06c(void);
extern void func_ov013_0206fbbc(void);
extern void func_ov013_02070e40(s32 useAlt);
extern void func_ov027_020b9098(void *panel, void *callback);
extern PanelObject *func_ov027_020b90a4(void *panel, int id);
extern void func_ov027_020b9620(void *panel, PanelObject *object);
extern void ApplySelectedSubitemValues_020b94fc(void *panel, PanelObject *object, s32 useAlt);

void ResetPanelLayoutClearFlag_02072674(void) {
    PanelObject *object;
    u8 *panel;

    func_ov002_020620fc(0);
    func_ov013_02070aa0();
    g_panelState_02074ce0->isLocked = FALSE;
    func_ov013_0206f06c();
    func_ov027_020b9098(g_panelState_02074ce0->panel, NULL);
    func_ov013_0206fbbc();
    object = func_ov027_020b90a4(g_panelState_02074ce0->panel, 0);
    func_ov027_020b9620(g_panelState_02074ce0->panel, object);
    object = func_ov027_020b90a4(g_panelState_02074ce0->panel, 2);
    func_ov027_020b9620(g_panelState_02074ce0->panel, object);
    object = func_ov027_020b90a4(g_panelState_02074ce0->panel, 3);
    func_ov027_020b9620(g_panelState_02074ce0->panel, object);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 2);
    ApplySelectedSubitemValues_020b94fc(panel, object, 1);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 3);
    ApplySelectedSubitemValues_020b94fc(panel, object, 1);
    panel = g_panelState_02074ce0->panel;
    object = func_ov027_020b90a4(panel, 5);
    func_ov027_020b9620(panel, object);
    func_ov013_02070e40(1);
}
