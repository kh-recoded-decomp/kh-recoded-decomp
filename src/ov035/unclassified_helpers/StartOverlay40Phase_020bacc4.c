#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x3c];
    int loadedOverlayId;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern char OverlayId40_00000028[];
extern void func_02029f78(int processor, int overlayId);
extern void func_ov040_020bd730(int arg);

void StartOverlay40Phase_020bacc4(int arg)
{
    g_movieContext_020bc4e0->loadedOverlayId = (int)OverlayId40_00000028;
    func_02029f78(0, (int)OverlayId40_00000028);
    func_ov040_020bd730(arg);
}