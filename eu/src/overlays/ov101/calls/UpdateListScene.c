#include "src/overlays/ov101/ListSceneState.h"

extern void (*const gOv101Callbacks[])(ListSceneState *scene);
extern u32 GetStatePhase(void);
extern void DrawListPanelText(int page, ListSceneState *scene);
extern void UpdateDescriptionScrollInput(ListSceneState *scene);
extern void InitStateLists(ListSceneState *scene);
extern void UpdatePageBufferPositions(ListSceneState *scene);

void UpdateListScene(ListSceneState *scene)
{
    void (*callback)(ListSceneState *) = gOv101Callbacks[GetStatePhase()];
    if (callback != NULL) {
        callback(scene);
    }
    /* Refresh the caption every sixty frames, alternating its phase. */
    if (++scene->captionRefreshFrames >= 60) {
        scene->captionRefreshFrames = 0;
        scene->captionRefreshPhase = (scene->captionRefreshPhase + 1) % 2;
        DrawListPanelText(0, scene);
    }
    UpdateDescriptionScrollInput(scene);
    InitStateLists(scene);
    UpdatePageBufferPositions(scene);
}
