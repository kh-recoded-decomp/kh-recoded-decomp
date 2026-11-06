#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    BOOL waitingForConfirm;
    u8 pad_40[0x100 - 0x40];
    u16 confirmTimer;
} PanelScene;

extern s32 GetFieldSessionState(void);
extern BOOL IsSessionFlagSet(u32 value);
extern int GetScriptHandlerSlot7Index(void);
extern BOOL RequestPanelModeWithConditionalTimerMode2(int choice);
extern s32 GetLoadedSubsceneMode(void);

void UpdatePanelConfirmTimer(PanelScene *panel)
{
    if (panel->confirmTimer != 0) {
        if (panel->confirmTimer == 1) {
            if (GetLoadedSubsceneMode() != 2 && RequestPanelModeWithConditionalTimerMode2(2)) {
                panel->waitingForConfirm = TRUE;
                if (GetScriptHandlerSlot7Index() == 0 && IsSessionFlagSet(0x370b)) {
                    panel->confirmTimer = 0;
                } else {
                    panel->confirmTimer = 2;
                }
            }
        } else {
            panel->confirmTimer++;
            if (panel->confirmTimer >= 0x71) {
                int choice = (GetFieldSessionState() == 10) ? 1 : 0;
                if (choice != -1 && RequestPanelModeWithConditionalTimerMode2(choice)) {
                    panel->waitingForConfirm = FALSE;
                    panel->confirmTimer = 0;
                }
            }
        }
    }
}
