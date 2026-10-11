#ifndef OV101_LIST_SCENE_STATE_H
#define OV101_LIST_SCENE_STATE_H

#include "nitro/types.h"

typedef struct PageInteractionBounds {
    s32 id;
    s32 originX;
    s32 originY;
    u8 pad000c[8];
    s16 minX;
    s16 minY;
    s16 maxX;
    s16 maxY;
} PageInteractionBounds;

typedef struct PageInteractionClip {
    s16 minX;
    s16 minY;
    s16 maxX;
    s16 maxY;
} PageInteractionClip;

/* Shared control-field view of the EU list scene. Rendering/resource views
 * describe the intervening storage separately. */
typedef struct ListSceneState {
    s32 activeList;
    s32 activePage;
    BOOL interactionActive;
    u8 pad000c[0xcd50 - 0x0c];
    PageInteractionBounds interactionBounds;
    u8 padcd6c[0xcfd8 - 0xcd6c];
    s32 captionRefreshFrames;
    s32 captionRefreshPhase;
    u32 handlerPhase;
    u8 padcfe4[0xdbd4 - 0xcfe4];
    PageInteractionClip interactionClip;
} ListSceneState;

typedef char ListRefreshCounterMustStartAtCfd8[
    (u32)&((ListSceneState *)0)->captionRefreshFrames == 0xcfd8 ? 1 : -1];
typedef char ListHandlerPhaseMustStartAtCfe0[
    (u32)&((ListSceneState *)0)->handlerPhase == 0xcfe0 ? 1 : -1];

#endif
