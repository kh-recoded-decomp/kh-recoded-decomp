#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_0000[0x27f1];
    u8 panelOpen : 1;
    u8 battleMode : 3;
    u8 extra : 4;
    u8 pad_27F2[0x146];
    int pendingPanel;
} FieldState;

extern FieldState *data_ov001_020a0460;
extern BOOL func_ov001_0207d210(BOOL wide);
extern void func_ov001_0207d384(int mode);

void HandleFieldPanelCommand_02063ccc(int command)
{
    FieldState *field = data_ov001_020a0460;

    switch (command) {
    case 0:
        if (!field->panelOpen) {
            func_ov001_0207d210(FALSE);
            field->panelOpen = TRUE;
        }
        break;
    case 1:
    case 3:
        if (!field->panelOpen) {
            func_ov001_0207d210(FALSE);
            field->panelOpen = TRUE;
        }
        func_ov001_0207d384(1);
        break;
    case 2:
        func_ov001_0207d384(0);
        break;
    case 4:
        field->pendingPanel = 0;
        break;
    }
}
