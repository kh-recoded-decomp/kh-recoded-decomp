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

extern FadeLevelTable data_ov000_02063848;
extern void func_ov000_02061b88(int value, int waitVBlank);

BOOL StepPanelFadeIn_02063108(PanelFade *fade)
{
    FadeLevelTable table = data_ov000_02063848;
    BOOL done = FALSE;

    fade->frame++;
    func_ov000_02061b88(table.funcs[fade->direction](fade), 0);
    if (fade->frame >= fade->fadeInFrames) {
        done = TRUE;
    }
    return done;
}
