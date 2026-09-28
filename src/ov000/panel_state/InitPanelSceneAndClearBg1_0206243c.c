#include "nitro/types.h"

typedef struct {
    u32 resourceId;
    u8 pad_04[0x90];
    u8 animState[0x78];
    void *model;
    u8 pad_110[0x5c];
    u8 blendTable[0x2c];
    u32 animationActive;
    u32 animationFinished;
} Panel;

extern void func_0202ecf8(void *animState, u32 resourceKey, int flags, int count);
extern void selectJointAnimationBlend_0202f2cc(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void func_0201a3c4(void *model, BOOL enable, u32 polygonAttrMask);
extern void InitPanelCamera_020615b8(Panel *panel);
extern void *G2_GetBG1CharPtr_020070cc(void);
extern void *G2S_GetBG1CharPtr_02007100(void);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void *G2S_GetBG1ScrPtr_02006e68(void);
/* Non-void return keeps the original call scheduling */
extern void *func_01ff8740(u32 value, void *dest, u32 size);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern BOOL func_0204dd4c(int handleIndex, u16 streamId);

void InitPanelSceneAndClearBg1_0206243c(Panel *panel)
{
    func_0202ecf8(panel->animState, ((panel->resourceId + 0x8000) & 0xfffffc) << 7 | 0x80000000, 1, 0xe);
    selectJointAnimationBlend_0202f2cc(panel->animState, 0, panel->blendTable, 0);
    selectJointAnimationBlend_0202f2cc(panel->animState, 2, panel->blendTable, 0);
    func_0201a3c4(panel->model, TRUE, 0x30);
    func_0201a3c4(panel->model, TRUE, 0x3f000000);
    func_0201a3c4(panel->model, TRUE, 0x1f0000);
    func_0201a3c4(panel->model, TRUE, 0x800);
    panel->animationActive = 1;
    panel->animationFinished = 0;
    InitPanelCamera_020615b8(panel);
    func_01ff8740(0, G2_GetBG1CharPtr_020070cc(), 0xc000);
    func_01ff8740(0, G2S_GetBG1CharPtr_02007100(), 0xc000);
    func_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x800);
    func_01ff8740(0, G2S_GetBG1ScrPtr_02006e68(), 0x800);
    if (!IsSoundStreamActive_0204ded4(0)) {
        func_0204dd4c(0, 0);
    }
}
