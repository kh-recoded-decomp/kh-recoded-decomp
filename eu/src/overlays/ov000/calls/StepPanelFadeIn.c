#include "nitro/types.h"

typedef struct PanelFade PanelFade;
typedef int (*FadeLevelFunc)(PanelFade *fade);

struct PanelFade {
    u8 pad_0[0x38];
    s32 direction;
    s32 frame;
    s32 fadeInFrames;
    s32 fadeOutFrames;
};

typedef struct FadeLevelTable {
    FadeLevelFunc funcs[2];
} FadeLevelTable;

extern FadeLevelTable gTitleScreenInputHandlers;
extern void func_ov000_02061b88(int value, int waitVBlank);

BOOL StepPanelFadeIn(PanelFade *fade)
{
    FadeLevelTable table = gTitleScreenInputHandlers;
    BOOL done = FALSE;

    fade->frame++;
    func_ov000_02061b88(table.funcs[fade->direction](fade), 0);
    if (fade->frame >= fade->fadeInFrames) {
        done = TRUE;
    }
    return done;
}
