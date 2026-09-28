#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x3c];
    int loadedOverlayId;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern void func_ov040_020bd990(void);
extern void func_02029f98(int processor, int overlayId);

void EndOverlay40Phase_020bace8(void) {
    MovieContext *context = g_movieContext_020bc4e0;

    func_ov040_020bd990();
    func_02029f98(0, context->loadedOverlayId);
    context->loadedOverlayId = -1;
}
