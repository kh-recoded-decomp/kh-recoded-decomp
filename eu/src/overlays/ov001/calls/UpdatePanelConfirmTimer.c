#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    BOOL waitingForConfirm;
    u8 pad_40[0x100 - 0x40];
    u16 confirmTimer;
} PanelScene;

extern s32 func_ov001_02063a38(void);
extern BOOL IsSessionFlagSet(u32 value);
extern int func_ov001_02064784(void);
extern BOOL func_ov001_0207b360(int choice);
extern s32 func_ov001_0207b3f4(void);

void UpdatePanelConfirmTimer(PanelScene *panel)
{
    if (panel->confirmTimer != 0) {
        if (panel->confirmTimer == 1) {
            if (func_ov001_0207b3f4() != 2 && func_ov001_0207b360(2)) {
                panel->waitingForConfirm = TRUE;
                if (func_ov001_02064784() == 0 && IsSessionFlagSet(0x370b)) {
                    panel->confirmTimer = 0;
                } else {
                    panel->confirmTimer = 2;
                }
            }
        } else {
            panel->confirmTimer++;
            if (panel->confirmTimer >= 0x71) {
                int choice = (func_ov001_02063a38() == 10) ? 1 : 0;
                if (choice != -1 && func_ov001_0207b360(choice)) {
                    panel->waitingForConfirm = FALSE;
                    panel->confirmTimer = 0;
                }
            }
        }
    }
}
