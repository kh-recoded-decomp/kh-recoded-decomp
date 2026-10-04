#include "nitro/types.h"

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} Rect16;

typedef struct {
    int handle;
    int x;
    int y;
    u8 pad_0C[8];
    Rect16 bounds;
} SlotItem;

typedef struct {
    u8 pad_0000[0xcde8];
    SlotItem dragItem;
    u8 pad_ce04[0xd1c4 - 0xce04];
    int touchActive;
    u8 pad_d1c8[0xd1ec - 0xd1c8];
    Rect16 dragBounds;
} SceneWork;

extern SceneWork *g_sceneWork_020c50e0;
extern void func_ov039_020bc03c(int value);

void UpdateDragAreaBounds_020c1ca8(void)
{
    SceneWork *work = g_sceneWork_020c50e0;
    SlotItem *item;
    Rect16 *drag;

    work->touchActive = 0;
    func_ov039_020bc03c(0);
    drag = &g_sceneWork_020c50e0->dragBounds;
    item = &work->dragItem;
    drag->right = item->x + item->bounds.right;
    drag->bottom = item->y + item->bounds.bottom;
    drag->left = item->x + item->bounds.left;
    drag->top = item->y + item->bounds.top;
}
