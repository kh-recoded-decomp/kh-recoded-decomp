#include "nitro/types.h"

typedef struct MenuIntroContext {
    u8 pad_00[8];
    s32 step;
} MenuIntroContext;

extern MenuIntroContext *g_context_0206c464;
extern void ClosePanelSelectorAll_020648c0(void);
extern void DrawMenuLabels_020643a0(void);

void EnterMenuIntroState(void)
{
    ClosePanelSelectorAll_020648c0();
    DrawMenuLabels_020643a0();
    g_context_0206c464->step = 0;
}
