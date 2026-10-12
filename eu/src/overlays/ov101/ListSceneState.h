#ifndef OV101_LIST_SCENE_STATE_H
#define OV101_LIST_SCENE_STATE_H

#include "nitro/types.h"
#include "src/overlays/ov101/ScrollPanelState.h"

typedef struct ListTextPage {
    u16 *lines[18];
    s32 lineCount;
} ListTextPage;

typedef struct ListTextArchiveView {
    void *file;
    u32 count;
    u8 *payload;
} ListTextArchiveView;

typedef struct ListTextLayer {
    u8 storage[0x34];
} ListTextLayer;

typedef struct PageInteractionBounds {
    s32 id;
    s32 originX;
    s32 originY;
    u8 pad000c[8];
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} PageInteractionBounds;

typedef struct PageInteractionClip {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
} PageInteractionClip;

typedef struct PageTrackRect {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} PageTrackRect;

typedef struct PageScrollDrag {
    PageInteractionClip clip;
    PageTrackRect track;
    BOOL grabbed;
    s32 unknown14;
    s32 dragDelta;
    s32 dragStartY;
    s32 dragCurrentY;
    s32 dragStartScroll;
    s32 lastY;
    s32 previousY;
    BOOL inertiaActive;
    s32 inertiaTarget;
} PageScrollDrag;

/* Shared control-field view of the EU list scene. Rendering/resource views
 * describe the intervening storage separately. */
typedef struct ListSceneState {
    s32 activeList;
    s32 activePage;
    BOOL interactionActive;
    u8 pad000c[0x44 - 0x0c];
    ListTextLayer textLayers[4];
    u8 pad0114[0xcb74 - 0x114];
    PageInteractionBounds scrollTrackItems[2];
    u8 padcbac[0xcd50 - 0xcbac];
    PageInteractionBounds interactionBounds;
    Ov101ScrollPanel panels[2];
    u8 padce04[0xce64 - 0xce04];
    s32 unknownCe64;
    s32 listPages[40];
    s32 listPageCounts[40];
    ListTextArchiveView textArchives[3];
    u8 padcfcc[0xcfd8 - 0xcfcc];
    s32 captionRefreshFrames;
    s32 captionRefreshPhase;
    u32 handlerPhase;
    s32 handlerStep;
    s32 handlerPhaseTimer;
    ListTextPage textPages[40];
    s32 pageScrollTarget;
    s32 pageScrollCurrent;
    PageScrollDrag pageDrag;
} ListSceneState;

typedef char ListRefreshCounterMustStartAtCfd8[
    (u32)&((ListSceneState *)0)->captionRefreshFrames == 0xcfd8 ? 1 : -1];
typedef char ListHandlerPhaseMustStartAtCfe0[
    (u32)&((ListSceneState *)0)->handlerPhase == 0xcfe0 ? 1 : -1];
typedef char ListPagesMustStartAtCe68[
    (u32)&((ListSceneState *)0)->listPages == 0xce68 ? 1 : -1];
typedef char ListPageCountsMustStartAtCf08[
    (u32)&((ListSceneState *)0)->listPageCounts == 0xcf08 ? 1 : -1];
typedef char ListPageInertiaFlagMustStartAtDc04[
    (u32)&((ListSceneState *)0)->pageDrag.inertiaActive == 0xdc04 ? 1 : -1];
typedef char ListPageDragOffsetCheck[
    (u32)&((ListSceneState *)0)->pageDrag == 0xdbd4 ? 1 : -1];
typedef char ListPageDragSizeCheck[sizeof(PageScrollDrag) == 0x38 ? 1 : -1];
typedef char ListScrollTrackItemsOffsetCheck[
    (u32)&((ListSceneState *)0)->scrollTrackItems == 0xcb74 ? 1 : -1];
typedef char ListInteractionBoundsSizeCheck[
    sizeof(PageInteractionBounds) == 0x1c ? 1 : -1];
typedef char ListTextPageSizeCheck[sizeof(ListTextPage) == 0x4c ? 1 : -1];
typedef char ListTextPagesOffsetCheck[
    (u32)&((ListSceneState *)0)->textPages == 0xcfec ? 1 : -1];
typedef char ListPrimaryPanelOffsetCheck[
    (u32)&((ListSceneState *)0)->panels == 0xcd6c ? 1 : -1];
typedef char ListSceneSizeCheck[sizeof(ListSceneState) == 0xdc0c ? 1 : -1];
typedef char ListTextArchiveViewSizeCheck[
    sizeof(ListTextArchiveView) == 12 ? 1 : -1];
typedef char ListTextLayersOffsetCheck[
    (u32)&((ListSceneState *)0)->textLayers == 0x44 ? 1 : -1];

#endif
