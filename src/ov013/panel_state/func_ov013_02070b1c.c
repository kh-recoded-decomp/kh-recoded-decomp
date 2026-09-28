#include "nitro/types.h"

typedef struct Overlay27Timing {
    u8 pad_00[0x4];
    s16 angle;
    u8 pad_06[0xa - 0x6];
    s16 width;
    s16 height;
} Overlay27Timing;

typedef struct PanelState {
    u8 pad_00[0x98];
    u8 flags;
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern Overlay27Timing *func_ov027_020b8184(u8 *context, int entryId);
extern void *G2S_GetBG0ScrPtr_02006e14(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);

void func_ov013_02070b1c(void) {
    Overlay27Timing *timing = func_ov027_020b8184((u8 *)g_panelState_02074ce0 + 0x350, 1);
    s32 size = timing->width * timing->height * 2;
    void *dest = (u8 *)G2S_GetBG0ScrPtr_02006e14() + (timing->angle << 6);
    func_01ff8740(0, dest, size);
    g_panelState_02074ce0->flags = g_panelState_02074ce0->flags & ~4;
}
