#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 opaque[0x34];
} TextLayer;

typedef struct {
    TextLayer textLayer;
    TextLayer markerLayer;
    u16 textScreen[0x400];
    u16 markerScreen[0x400];
    u8 pad_1068[0x10940 - 0x1068];
} ScrollPanel;

typedef struct {
    u8 pad_00[0x30];
    ScrollPanel panels[2];
    u8 pad_212b0[0x23a94 - 0x212b0];
    NNSG2dFont mainFont;
    void *mainFontFile;
    NNSG2dFont subFont;
    void *subFontFile;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;

extern void func_020169ec(NNSG2dFont *font, void *fontFile);
extern void func_ov004_02063988(TextLayer *layer, int columns, u16 *screen, int bgSlot);

void InitScrollTextLayers_02063a28(void)
{
    func_020169ec(&g_scrollText_020645a0.work->mainFont, g_scrollText_020645a0.work->mainFontFile);
    func_020169ec(&g_scrollText_020645a0.work->subFont, g_scrollText_020645a0.work->subFontFile);
    func_ov004_02063988(&g_scrollText_020645a0.work->panels[0].textLayer, 0x20, g_scrollText_020645a0.work->panels[0].textScreen, 5);
    func_ov004_02063988(&g_scrollText_020645a0.work->panels[0].markerLayer, 3, g_scrollText_020645a0.work->panels[0].markerScreen, 5);
    func_ov004_02063988(&g_scrollText_020645a0.work->panels[1].textLayer, 0x20, g_scrollText_020645a0.work->panels[1].textScreen, 0x15);
    func_ov004_02063988(&g_scrollText_020645a0.work->panels[1].markerLayer, 3, g_scrollText_020645a0.work->panels[1].markerScreen, 0x15);
}
