#include "nitro/types.h"

typedef struct {
    s8 mode;
    s8 kind;
    s16 x;
    s16 y;
} StartParams;

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    u16 flags;
    u8 pad_08[0x10];
    u32 timer;
    u8 pad_1c[0x20];
    s8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void ClearFieldCounters_02064dc8(void);

void ApplyStartParams_020bb518(StartParams *params)
{
    g_activeState_020bc800->x = params->x;
    g_activeState_020bc800->y = params->y;
    g_activeState_020bc800->kind = params->kind;
    g_activeState_020bc800->flags = 3;
    g_activeState_020bc800->flags |= 0x20;
    g_activeState_020bc800->mode = params->mode;
    g_activeState_020bc800->timer = 0;
    ClearFieldCounters_02064dc8();
}
