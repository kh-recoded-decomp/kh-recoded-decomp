#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_00[4];
    u8 selection;
    u8 pad_05[0xe4 - 5];
    int pendingAction;
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern void InitMenuCursorState(unsigned int value);

void ResetPanelSelection_02070c58(void)
{
    data_ov015_0207e960->selection = 0;
    data_ov015_0207e960->pendingAction = 0;
    InitMenuCursorState(0);
}
