#include "src/graphics/CameraState.h"

typedef struct Context {
    u8 pad_000[0x104];
    u8 slotMask;
} Context;

extern Context *data_ov001_020a04ec;
extern int *func_01ffb2f8(int arg0, int arg1, int arg2);

BOOL PlaceSlotPanelAtWorldPosition(int slot, const VecFx32 *position, int animate)
{
    Context *context;
    u8 *panel;
    int screenX;
    int screenY;
    int frame;

    context = data_ov001_020a04ec;
    panel = NULL;
    if (context == NULL || (u16)slot >= 4) {
        return FALSE;
    }
    context->slotMask |= 1 << slot;
    switch (slot) {
    case 2:
        panel = (u8 *)context + 0x704;
        break;
    case 3:
        panel = (u8 *)context + 0x808;
        break;
    }
    ProjectWorldPositionWithSavedCamera(position, &screenX, &screenY);
    frame = 0;
    *(int *)(panel + 0xa4) = (s64)(screenX - 0x80) * 0xcccd / 0x80;
    *(int *)(panel + 0xa8) = -(int)((s64)(screenY - 0x60) * 0x999a / 0x60);
    if (animate) {
        frame = 1;
    }
    func_01ffb2f8((int)panel, 3, frame << 12);
    return TRUE;
}
