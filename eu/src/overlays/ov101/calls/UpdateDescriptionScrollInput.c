#include "src/overlays/ov101/ListSceneState.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad0000[4];
    s16 x;
    s16 y;
    u16 state;
} ListTouchInput;

extern ListSceneState *data_ov101_020c5920;

extern ListTouchInput *GetMenuInputState(void);
extern void StepPageScrollPosition(int trackIndex);
extern int GetPageScrollPosition(int trackIndex);
extern BOOL IsPageScrollSettled(int trackIndex);
extern void SetPageScrollValue(int trackIndex, int row);
extern void ResetPageScrollValue(int trackIndex);
extern void SetPageScrollTarget(int trackIndex, int row);
extern void UpdateScrollPanel(int listIndex, ListSceneState *scene);
extern void DrawListPanelText(int listIndex, ListSceneState *scene);
extern fx32 FX_Div(fx32 numer, fx32 denom);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800LL) >> 12);
}

void UpdateDescriptionScrollInput(ListSceneState *scene)
{
    PageScrollDrag *drag = &data_ov101_020c5920->pageDrag;
    Ov101ScrollPanel *bar = &scene->panels[1];
    ListTouchInput *touch = GetMenuInputState();
    PageInteractionBounds *lowerItem;
    PageInteractionBounds *upperItem;
    int halfHeight;
    int top;
    int bottom;
    int y;
    fx32 ratio;
    int maxPos;

    lowerItem = &scene->scrollTrackItems[0];
    upperItem = &scene->scrollTrackItems[1];
    drag->track.right = lowerItem->originX + lowerItem->x1;
    drag->track.bottom = lowerItem->originY + lowerItem->y1;
    drag->track.left = lowerItem->originX + lowerItem->x0;
    drag->track.top = upperItem->originY + upperItem->y0;

    if (((touch->state & 3) == 0 || (touch->state & 3) == 2) && drag->inertiaActive != 0) {
        StepPageScrollPosition(0);
        bar->scroll = GetPageScrollPosition(0);
        UpdateScrollPanel(1, scene);
        DrawListPanelText(1, scene);
        IsPageScrollSettled(0);
    }

    if ((touch->state & 3) == 0) {
        return;
    }
    if ((touch->state & 3) == 1) {
        if (drag->clip.minX <= touch->x && touch->x <= drag->clip.maxX && drag->clip.minY <= touch->y && touch->y <= drag->clip.maxY) {
            drag->grabbed = 1;
        }
    }
    if ((touch->state & 3) == 2) {
        drag->grabbed = 0;
        drag->unknown14 = 0;
        drag->dragDelta = 0;
        drag->dragStartY = 0;
        drag->dragCurrentY = 0;
        drag->dragStartScroll = 0;
        scene->interactionActive = 0;
        return;
    }
    if (drag->grabbed != 0) {
        if (touch->state & 1) {
            halfHeight = (drag->track.top - drag->track.bottom) / 2;
            bottom = drag->clip.minY + halfHeight;
            top = drag->clip.maxY - halfHeight;
            scene->interactionActive = 1;
            drag->inertiaActive = 0;
            y = touch->y;
            if (y > top) {
                y = top;
            }
            y -= bottom;
            if (y < 0) {
                y = 0;
            }
            ratio = FX_Div(y << 12, (top - bottom) << 12);
            bar->scroll = (FxMul((bar->totalRows - bar->pageRows) << 12, ratio) + 0x800) >> 12;
            UpdateScrollPanel(1, scene);
            DrawListPanelText(1, scene);
        }
        return;
    }
    if ((touch->state & 3) == 1) {
        scene->interactionActive = 1;
        drag->dragStartY = touch->y;
        drag->dragStartScroll = bar->scroll;
        drag->lastY = touch->y;
        drag->inertiaActive = 0;
        ResetPageScrollValue(0);
    }
    if ((touch->state & 3) == 3) {
        drag->dragCurrentY = touch->y;
        drag->dragDelta = drag->dragCurrentY - drag->dragStartY;
        bar->scroll = drag->dragStartScroll - drag->dragDelta / 16;
        maxPos = bar->totalRows - bar->pageRows;
        if (bar->scroll > maxPos) {
            bar->scroll = maxPos;
        }
        if (bar->scroll < 0) {
            bar->scroll = 0;
        }
        UpdateScrollPanel(1, scene);
        DrawListPanelText(1, scene);
        drag->previousY = drag->lastY;
        drag->lastY = touch->y;
        drag->inertiaTarget = bar->scroll - (drag->lastY - drag->previousY) * 9 / 8;
        drag->inertiaActive = 1;
        if (drag->inertiaTarget < 0) {
            drag->inertiaTarget = 0;
        }
        maxPos = bar->totalRows - bar->pageRows;
        if (drag->inertiaTarget > maxPos) {
            drag->inertiaTarget = maxPos;
        }
        SetPageScrollValue(0, bar->scroll);
        SetPageScrollTarget(0, drag->inertiaTarget);
    }
}
