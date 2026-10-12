#include "src/overlays/ov101/ListSceneState.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)

extern void ReleaseStateBuffers(ListSceneState *scene);
extern void LoadPortraitSprites(ListSceneState *scene);
extern BOOL IsStateFlagSet(s32 set, s32 bit);
extern void SetOv101SlotEntryVisible(s32 list, s32 entry, s32 visible, ListSceneState *scene);
extern void SetEntryAnimFrame(s32 list, s32 entry, s32 frame, ListSceneState *scene);
extern void DrawListPanelText(s32 which, ListSceneState *scene);
extern void SetStatePhase(s32 phase);

void RunListScreenStep(ListSceneState *scene)
{
    Ov101ScrollPanel *panel;
    s32 i;
    s32 scroll;
    s32 highlighted;
    s32 owned;
    s32 list;
    u32 planes;

    switch (scene->handlerStep) {
    case 0:
        /* Keep BG0 hidden while its portraits and text are rebuilt. */
        planes = (REG_DISPCNT & 0x1f00) >> 8;
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes & ~1) << 8);
        ReleaseStateBuffers(scene);
        LoadPortraitSprites(scene);
        scene->handlerStep++;
        break;
    case 1:
        panel = &scene->panels[0];
        for (i = 0; i < panel->pageRows; i++) {
            scroll = panel->scroll;
            highlighted = IsStateFlagSet(2, scroll + i) != 0;
            owned = IsStateFlagSet(1, scroll + i);
            SetOv101SlotEntryVisible(0, i + 3, owned, scene);
            SetEntryAnimFrame(0, i + 3, highlighted, scene);
        }
        DrawListPanelText(-1, scene);
        planes = (REG_DISPCNT_SUB & 0x1f00) >> 8;
        list = scene->activeList;
        if (IsStateFlagSet(0, list) && scene->textPages[list].lineCount > 9) {
            planes |= 0x10;
        } else {
            planes &= ~0x10;
        }
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (planes << 8);
        scene->handlerStep++;
        break;
    case 2:
        planes = (REG_DISPCNT & 0x1f00) >> 8;
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes | 1) << 8);
        SetStatePhase(0);
        break;
    }
}
