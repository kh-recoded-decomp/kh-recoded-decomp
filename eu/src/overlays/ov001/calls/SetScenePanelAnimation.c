#include "nitro/types.h"

typedef struct ScenePanelAnim {
    u8 pad_000[0xD8];
    s16 tracks[5];
    u8 pad_0E2[0x22];
    u8 flags;
    u8 pad_105;
    s8 blendIndex;
    u8 pad_107;
} ScenePanelAnim;

typedef struct MenuScene {
    u8 pad_0000[0x18];
    ScenePanelAnim panels[16];
    u8 pad_1098[0x20];
    u8 animMode;
} MenuScene;

extern MenuScene *data_ov001_020a048c;

extern void BlendToAnimationTrack(ScenePanelAnim *state, u16 trackIndex, s16 *table, s16 blendIndex, int frameCount);
extern int *func_01ffb2f8(ScenePanelAnim *state, u16 trackIndex, int arg);

void SetScenePanelAnimation(int panelIndex, int blendIndex, int arg, BOOL keepFlag)
{
    MenuScene *scene = data_ov001_020a048c;
    ScenePanelAnim *panel = &scene->panels[panelIndex];
    int i;

    panel->blendIndex = blendIndex;
    if (!keepFlag) {
        panel->flags |= 2;
    } else {
        panel->flags &= ~2;
    }
    if (scene->animMode == 2) {
        for (i = 0; i < 5; i++) {
            if (panel->tracks[(u16)i] > 0) {
                BlendToAnimationTrack(panel, i, panel->tracks, blendIndex, 0);
                func_01ffb2f8(panel, i, arg);
            }
        }
    }
}
