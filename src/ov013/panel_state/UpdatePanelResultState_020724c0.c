#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x3];
    s8 resultMode;
    u8 pad_04[0x2bc - 0x4];
    s32 resultState;
    u8 pad_2C0[0x2f0 - 0x2c0];
    s8 clearCount;
    u8 pad_2F1[0x6818 - 0x2f1];
    u8 panel[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern int data_0206085c;
extern BOOL IsButtonBPressed_020632c8(void);
extern u16 *func_ov002_02062000(void);
extern u32 func_ov002_0206655c(void);
extern void StartPanelFadeOut(int mode);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov013_02070aa0(void);
extern void func_ov013_0206f06c(void);
extern void func_ov013_020716e4(int mode);
extern void func_ov013_0206f978(int mode);
extern void func_ov027_020b8ca8(void *panel, int value);

void UpdatePanelResultState_020724c0(void) {
    switch (g_panelState_02074ce0->resultState) {
    case 0:
        if (IsButtonBPressed_020632c8()) {
            PlaySoundEffect_0204d924(2, 2);
            func_ov013_02070aa0();
            func_ov013_0206f06c();
            func_ov013_020716e4(1);
            return;
        }
        func_ov027_020b8ca8(g_panelState_02074ce0->panel, *func_ov002_02062000());
        if ((u8)(s8)(g_panelState_02074ce0->resultMode - 1) <= 1) {
            g_panelState_02074ce0->resultState = 5;
        }
        break;
    case 5:
        g_panelState_02074ce0->resultState = 10;
        break;
    case 10:
        if (g_panelState_02074ce0->resultMode == 1) {
            data_0206085c = 0;
            if ((g_panelState_02074ce0->clearCount + 1) % 10 != 0) {
                g_panelState_02074ce0->resultMode = 0;
                func_ov013_02070aa0();
                func_ov013_0206f06c();
                g_panelState_02074ce0->resultState = 20;
            } else {
                StartPanelFadeOut(3);
                g_panelState_02074ce0->resultState = 35;
            }
        } else if (g_panelState_02074ce0->resultMode == 2) {
            func_ov013_02070aa0();
            func_ov013_0206f06c();
            func_ov013_020716e4(1);
        }
        break;
    case 20:
        StartPanelFadeOut(1);
        g_panelState_02074ce0->resultState = 30;
        break;
    case 30:
        if (func_ov002_0206655c()) {
            func_ov013_020716e4(6);
        }
        break;
    case 35:
        if (func_ov002_0206655c()) {
            func_ov013_0206f978(0);
        }
        break;
    }
}
