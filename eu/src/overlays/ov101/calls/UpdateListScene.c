#include "src/overlays/ov101/ListSceneState.h"

extern void (*const gOv101Callbacks[])(ListSceneState *scene);
extern u32 GetStatePhase(void);
extern void func_ov101_020bfab8(int page, ListSceneState *scene);
extern void func_ov101_020c0df4(ListSceneState *scene);
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
        func_ov101_020bfab8(0, scene);
    }
    func_ov101_020c0df4(scene);
    InitStateLists(scene);
    UpdatePageBufferPositions(scene);
}
