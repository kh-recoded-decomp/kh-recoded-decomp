#include "nitro/types.h"

typedef struct {
    u32 handle;
    u8 pad_04[4];
    u32 entryCount;
    u8 textWidget[0x34];
} ResourceCacheState;

extern ResourceCacheState *g_resourceCache_020b6f60;
extern void func_02001574(void *widget, int mode);
extern int func_ov001_020711d4(void);
extern void func_0200160c(void *widget, u32 x, u32 y, u32 color, u32 flags, int text,
                          u32 overrideValue, int maxWidth);
extern void func_02001520(void *widget);

void DrawCacheHeaderText_020b5a30(int text)
{
    ResourceCacheState *state = g_resourceCache_020b6f60;
    void *widget;
    u32 overrideValue;

    if (state != NULL && text != 0 && state->entryCount != 0) {
        widget = state->textWidget;
        func_02001574(widget, 1);
        overrideValue = func_ov001_020711d4();
        func_0200160c(widget, 0xab, 3, 2, 0x821, text, overrideValue, 0xa8);
        func_02001520(widget);
    }
}
