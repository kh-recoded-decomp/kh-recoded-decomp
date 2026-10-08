#include "nitro/types.h"

typedef struct RenderFlags {
    u8 pad00[0x1c];
    u8 visible : 1;
    u8 active : 1;
    u8 padBits : 6;
    u8 pad1d[3];
    s16 slotIds[8];
} RenderFlags;

typedef struct ModelState {
    u8 pad00[0x22];
    u8 kind : 3;
    u8 kindPad : 5;
    u8 pad23;
    RenderFlags render;
} ModelState;

void ResetModelSlotIds_020aa108(ModelState *state)
{
    volatile RenderFlags *render;
    int i;

    for (i = 0; i < 8; i++) {
        state->render.slotIds[i] = -1;
    }
    switch (state->kind) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        render = &state->render;
        render->visible = 0;
        render->active = 0;
        break;
    }
}
