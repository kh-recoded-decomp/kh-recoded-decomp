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

extern PanelPhaseTable data_ov000_02063850;
extern PanelStateHandlers data_ov000_02063888[];
extern PanelStateHandlers data_ov000_0206388c[];

extern Panel *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void SetPanelMode_02061dc4(Panel *panel, u32 mode);
extern void NNS_FndInitListWithOffset0_0204f11c(void *list);
extern u16 AdvanceAnimationTracks_0202ef24(void *animation, int delta);
extern int func_0202f4b8(void *animation, int track);
extern int *func_01ffb2f8(void *animation, int track, int frame);
extern void SceneNode_Draw_01ffb12c(void *animation);

int UpdateTitlePanel_02063424(void)
{
    Panel *panel = NNSi_FndGetCurrentRootHeap_0202a764();
    PanelPhaseTable phases = data_ov000_02063850;
    int result = 0;

    if (phases.funcs[panel->phase] != NULL) {
        panel->phase = phases.funcs[panel->phase](panel);
    } else if (panel->state >= 0) {
        int mode = data_ov000_02063888[panel->state].first(panel);

        if (mode == -2) {
            data_ov000_0206388c[panel->state].first(panel);
            result = -2;
        } else if (mode != -1 && mode != panel->state) {
            SetPanelMode_02061dc4(panel, mode);
        }
    }
    if (panel->resetList) {
        NNS_FndInitListWithOffset0_0204f11c(panel->list);
    }
    if (panel->hasAnimation) {
        if (!panel->animationLooped && AdvanceAnimationTracks_0202ef24(panel->animation, 0x1000)) {
            int frame = func_0202f4b8(panel->animation, 0);

            func_01ffb2f8(panel->animation, 0, frame - 0x1000);
            func_01ffb2f8(panel->animation, 2, frame - 0x1000);
            panel->animationLooped = TRUE;
        }
        SceneNode_Draw_01ffb12c(panel->animation);
    }
    return result;
}
