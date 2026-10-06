#include "nitro/types.h"

typedef struct Panel Panel;
typedef int (*PanelPhaseFunc)(Panel *panel);
typedef int (*PanelStateFunc)(Panel *panel);

typedef struct PanelPhaseTable {
    PanelPhaseFunc funcs[4];
} PanelPhaseTable;

typedef struct PanelStateHandlers {
    PanelStateFunc first;
    PanelStateFunc second;
    PanelStateFunc third;
} PanelStateHandlers;

struct Panel {
    u8 pad_0[0x2c];
    s32 state;
    u8 pad_30[0x34 - 0x30];
    s32 phase;
    u8 pad_38[0x94 - 0x38];
    u8 animation[0x198 - 0x94];
    BOOL hasAnimation;
    BOOL animationLooped;
    u8 pad_1a0[0x224 - 0x1a0];
    u8 list[0x6658 - 0x224];
    BOOL resetList;
};

extern PanelPhaseTable gTitleScreenOptionHandlers;
extern PanelStateHandlers gPanelInitialStateHandler[];
extern PanelStateHandlers gPanelStateHandlers[];

extern Panel *NNSi_FndGetCurrentRootHeap(void);
extern void SetPanelMode(Panel *panel, u32 mode);
extern void NNS_FndInitListWithOffset0_0204f130(void *list);
extern u16 AdvanceAnimationTracks(void *animation, int delta);
extern int func_0202f4cc(void *animation, int track);
extern int *func_01ffb2f8(void *animation, int track, int frame);
extern void func_01ffb12c(void *animation);

int UpdateTitlePanel(void)
{
    Panel *panel = NNSi_FndGetCurrentRootHeap();
    PanelPhaseTable phases = gTitleScreenOptionHandlers;
    int result = 0;

    if (phases.funcs[panel->phase] != NULL) {
        panel->phase = phases.funcs[panel->phase](panel);
    } else if (panel->state >= 0) {
        int mode = gPanelInitialStateHandler[panel->state].first(panel);

        if (mode == -2) {
            gPanelStateHandlers[panel->state].first(panel);
            result = -2;
        } else if (mode != -1 && mode != panel->state) {
            SetPanelMode(panel, mode);
        }
    }
    if (panel->resetList) {
        NNS_FndInitListWithOffset0_0204f130(panel->list);
    }
    if (panel->hasAnimation) {
        if (!panel->animationLooped && AdvanceAnimationTracks(panel->animation, 0x1000)) {
            int frame = func_0202f4cc(panel->animation, 0);

            func_01ffb2f8(panel->animation, 0, frame - 0x1000);
            func_01ffb2f8(panel->animation, 2, frame - 0x1000);
            panel->animationLooped = TRUE;
        }
        func_01ffb12c(panel->animation);
    }
    return result;
}
