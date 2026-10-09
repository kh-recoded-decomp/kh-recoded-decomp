#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[8];
    s32 step;
} MenuContext;

extern MenuContext *g_context_0206c464;
extern void func_ov002_02062014(int value);
extern void StartPanelFadeIn(int value);
extern u32 func_ov002_0206655c(void);
extern void func_ov002_02064f6c(int state);

void RunMenuIntroStep_02064ff8(void)
{
    switch (g_context_0206c464->step) {
    case 0:
        func_ov002_02062014(1);
        g_context_0206c464->step = 10;
        break;
    case 10:
        StartPanelFadeIn(3);
        g_context_0206c464->step = 20;
        break;
    case 20:
        if (func_ov002_0206655c()) {
            func_ov002_02064f6c(1);
        }
        break;
    }
}
