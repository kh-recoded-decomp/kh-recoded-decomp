#include "src/overlays/ov101/ListSceneState.h"

extern ListSceneState *data_ov101_020c5920;
extern u16 data_02060500;
extern BOOL IsStateFlagSet(s32 set, s32 bit);
extern u32 GetStatePhase(void);
extern void SetStatePhase(u32 phase);
extern void PlaySoundEffect(s32 group, s32 id);
extern BOOL ScrollPanelPageUp(s32 panel, ListSceneState *scene);
extern void ResetPageScrollValue(s32 index);
extern void DrawListPanelText(s32 page, ListSceneState *scene);

void HandleListLeftInput(ListSceneState *scene)
{
    s32 list = scene->activeList;

    if (scene->activePage == 0 && scene->interactionActive == 0) {
        s32 pageCount;

        if (!IsStateFlagSet(0, list)) {
            return;
        }
        if (!(data_02060500 & 0x20)) {
            return;
        }
        if (GetStatePhase() == 1) {
            return;
        }
        pageCount = scene->listPageCounts[list];
        if (pageCount == 1) {
            return;
        }
        scene->listPages[list]--;
        if (scene->listPages[list] < 0) {
            scene->listPages[list] = pageCount - 1;
        }
        SetStatePhase(1);
        PlaySoundEffect(0, 1);
    } else {
        s32 previousList;

        if (!ScrollPanelPageUp(1, scene)) {
            return;
        }
        previousList = scene->activeList;
        ResetPageScrollValue(0);
        data_ov101_020c5920->pageDrag.inertiaActive = 0;
        DrawListPanelText(1, scene);
        if (!IsStateFlagSet(0, previousList)) {
            return;
        }
        if (!scene->interactionActive) {
            PlaySoundEffect(0, 0);
        }
    }
}
