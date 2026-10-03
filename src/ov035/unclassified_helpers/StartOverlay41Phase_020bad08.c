#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x34];
    int loadedOverlayId;
    u8 pad_40[0x78];
    u8 phaseState[1];
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern char OverlayId41_00000029[];
extern void func_02029f78(int processor, int overlayId);
extern void func_ov041_020bc504(void *params);
extern void func_ov041_020bc5c0(void *state, void *params);

void StartOverlay41Phase_020bad08(void)
{
    MovieContext *context = g_movieContext_020bc4e0;
    u8 params[0x2c];

    context->loadedOverlayId = (int)OverlayId41_00000029;
    func_02029f78(0, (int)OverlayId41_00000029);
    g_movieContext_020bc4e0->flags |= 0x40;
    func_ov041_020bc504(params);
    func_ov041_020bc5c0(context->phaseState, params);
}