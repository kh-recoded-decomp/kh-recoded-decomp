#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    int entryMode;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void InitMenuContext_0206331c(int entryMode);

void RefreshMenuContext_02062d0c(void)
{
    InitMenuContext_0206331c(g_panelState_0206c460->entryMode);
}
