#include "nitro/types.h"

typedef struct {
    u32 resourceId;
    u8 pad_04[0x90];
    u8 animState[0xd8];
    u8 blendTable[0x2c];
    u32 sceneReady;
    u32 animationFinished;
} Panel;

extern int func_0202b788(void);
extern void func_0202ecf8(void *animState, u32 resourceKey, int flags, int count);
extern void selectJointAnimationBlend_0202f2cc(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void InitPanelCamera_020615b8(Panel *panel);

void InitPanelScene_02061614(Panel *panel)
{
    if (panel->sceneReady != 0) {
        return;
    }
    func_0202ecf8(panel->animState,
                  ((panel->resourceId + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((func_0202b788() != 0) + 3) & 0x1ff,
                  1, 0xe);
    selectJointAnimationBlend_0202f2cc(panel->animState, 0, panel->blendTable, 0);
    selectJointAnimationBlend_0202f2cc(panel->animState, 2, panel->blendTable, 0);
    panel->animationFinished = 0;
    InitPanelCamera_020615b8(panel);
    panel->sceneReady = 1;
}
