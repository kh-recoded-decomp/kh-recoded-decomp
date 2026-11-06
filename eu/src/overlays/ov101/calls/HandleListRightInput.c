#include "src/overlays/ov101/ListSceneState.h"

extern ListSceneState *gListMenuGlobalStorage;
extern u16 gPadPressedStorage;
extern BOOL IsStateFlagSet(s32 set, s32 bit);
extern u32 GetStatePhase(void);
extern void SetStatePhase(u32 phase);
extern void PlaySoundEffect(s32 group, s32 id);
extern BOOL ScrollPanelPageDown(s32 panel, ListSceneState *scene);
extern void ResetPageScrollValue(s32 index);
extern void DrawListPanelText(s32 page, ListSceneState *scene);

void HandleListRightInput(ListSceneState *scene)
{
    s32 list = scene->activeList;

    if (scene->activePage == 0 && scene->interactionActive == 0) {
        s32 pageCount;

        if (!IsStateFlagSet(0, list)) {
            return;
        }
        if (!(gPadPressedStorage & 0x10) && !(gPadPressedStorage & 1)) {
            return;
        }
        if (GetStatePhase() == 1) {
            return;
        }
        pageCount = scene->listPageCounts[list];
        if (pageCount == 1) {
            return;
        }
        scene->listPages[list]++;
        if (scene->listPages[list] > pageCount - 1) {
            scene->listPages[list] = 0;
        }
        SetStatePhase(1);
        PlaySoundEffect(0, 1);
    } else {
        s32 previousList;

        if (!ScrollPanelPageDown(1, scene)) {
            return;
        }
        previousList = scene->activeList;
        ResetPageScrollValue(0);
        gListMenuGlobalStorage->pageDrag.inertiaActive = 0;
        DrawListPanelText(1, scene);
        if (!IsStateFlagSet(0, previousList)) {
            return;
        }
        if (!scene->interactionActive) {
            PlaySoundEffect(0, 0);
        }
    }
}
