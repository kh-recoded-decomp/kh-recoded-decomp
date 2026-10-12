#include "src/overlays/ov101/ListMenuData.h"

extern ListSceneState *data_ov101_020c5920;
extern BOOL ScrollPanelCursorDown(s32 panel, ListSceneState *scene);
extern void PlaySoundEffect(s32 bank, s32 sound);
extern BOOL IsStateFlagSet(s32 set, s32 bit);
extern void *SetStateFlag(s32 set, s32 bit);
extern void SetGlobalPackedBit(s32 bit);
extern void InitScrollPanel(ListScrollPanelConfig *config, ListSceneState *scene);
extern void ResetPageScrollValue(s32 index);
extern void SetStatePhase(u32 phase);
extern void DrawListPanelText(s32 page, ListSceneState *scene);

void HandleListDownInput(ListSceneState *scene)
{
    if (scene->activePage == 0 && scene->interactionActive == 0) {
        s32 list;
        Ov101ScrollPanel *panel;
        ListScrollPanelConfig config;

        if (!ScrollPanelCursorDown(0, scene)) {
            return;
        }
        panel = &scene->panels[0];
        scene->activeList = panel->scroll + panel->cursor;
        PlaySoundEffect(0, 0);
        list = scene->activeList;
        if (IsStateFlagSet(1, list)) {
            SetStateFlag(2, list);
            SetGlobalPackedBit(list + 0x1272);
        }
        list = scene->activeList;
        /* The selected list determines the secondary panel's text rows. */
        config = gSecondaryListScrollConfig;
        config.totalRows = scene->textPages[list].lineCount;
        InitScrollPanel(&config, scene);
        ResetPageScrollValue(0);
        data_ov101_020c5920->pageDrag.inertiaActive = 0;
        SetStatePhase(1);
    } else {
        s32 previousList;
        if (!ScrollPanelCursorDown(1, scene)) {
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
