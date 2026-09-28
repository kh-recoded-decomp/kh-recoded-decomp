#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    int loadedOverlayId;
    u8 pad_40[0x78];
    void *overlay41Buffer;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern void func_ov041_020bca3c(void **buffer);
extern void func_02029f98(int processor, int overlayId);

void EndOverlay41Phase_020bad64(void) {
    MovieContext *context = g_movieContext_020bc4e0;

    func_ov041_020bca3c(&context->overlay41Buffer);
    context->flags &= ~0x40;
    func_02029f98(0, context->loadedOverlayId);
    context->loadedOverlayId = -1;
}
