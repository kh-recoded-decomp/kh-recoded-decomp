#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0xc8c - 4];
    u8 uploads[0x1c];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);
extern void func_ov027_020b9e00(void *uploads, int slotId);
extern void func_ov027_020b9e60(void *uploads);

void RefreshSharedUploadSlot_020c13f0(void)
{
    MenuSharedState *state = func_ov039_020bc630();

    func_ov027_020b9e00(state->uploads, 0x1a);
    if ((state->flags & 2) == 0) {
        func_ov027_020b9e60(state->uploads);
    }
}
