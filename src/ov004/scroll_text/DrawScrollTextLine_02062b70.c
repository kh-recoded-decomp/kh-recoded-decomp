#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 *pixels;
} TextBuffer;

typedef struct {
    u8 pad_00[0x14];
    void *font;
    u8 pad_18[0x20 - 0x18];
    TextBuffer *buffer;
    u8 pad_24[0x34 - 0x24];
} TextLayer;

typedef struct {
    u8 pad_00[0x1c];
    TextLayer textLayer;
    TextLayer overlayLayer;
    u8 pad_84[0x10904 - 0x84];
    int objects[4];
    u8 pad_10914[0x10916 - 0x10914];
    u16 pendingDrop;
    u8 pad_10918[0x10940 - 0x10918];
} ScrollScreen;

typedef struct {
    u8 data[0xc];
} ScrollFont;

typedef struct {
    u8 data[0x6434];
} ObjManager;

typedef struct {
    u8 pad_00[0x14];
    ScrollScreen screens[2];
    u8 pad_21294[0x23a94 - 0x21294];
    ScrollFont fonts[4];
    u32 pad_23ac4[4];
    ObjManager objManagers[2];
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

typedef struct {
    int objectIndex;
    u16 code[4];
} ObjectMarker;

typedef struct {
    int x;
    int y;
} ObjectPosition;

extern ScrollTextGlobals g_scrollText_020645a0;
extern const ObjectMarker data_ov004_02063bb0[4];
extern const u16 data_ov004_02063ba8[];

extern void func_0204f13c(ObjManager *manager, int object, ObjectPosition *position);
extern void func_0204f378(ObjManager *manager, int object, int value);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void func_01ff8710(const void *src, void *dst, int size);

void DrawScrollTextLine_02062b70(const u16 *text, int align, int y, int screenIndex, int fontIndex, int highlight)
{
    ScrollTextWork *work = g_scrollText_020645a0.work;
    ScrollScreen *screen = &work->screens[screenIndex];
    int i;
    int color;
    ObjectPosition position;

    if (text[0] == 0x3e) {
        ObjManager *manager = &work->objManagers[screenIndex];
        int object;

        for (i = 0; i < 4; i++) {
            if (text[1] == data_ov004_02063bb0[i].code[0] && text[2] == data_ov004_02063bb0[i].code[1] &&
                text[3] == data_ov004_02063bb0[i].code[2] && text[4] == data_ov004_02063bb0[i].code[3]) {
                object = data_ov004_02063bb0[i].objectIndex;
                position.x = 0x80000;
                position.y = 0xc0000;
                func_0204f13c(manager, screen->objects[object], &position);
                func_0204f378(manager, screen->objects[object], 1);
                if (i == 1 && screen->pendingDrop == 0) {
                    screen->pendingDrop = 1;
                }
                return;
            }
        }
        return;
    }
    if (highlight != 0) {
        color = 7;
    } else if (fontIndex == 0 || align == 2) {
        color = 1;
    } else {
        color = 4;
    }
    if (y < 0) {
        CallVirtualHandlerSlot1_02001574(&screen->overlayLayer, 0);
        screen->overlayLayer.font = &g_scrollText_020645a0.work->fonts[fontIndex];
        DrawTextAnchored_020015a0(&screen->overlayLayer, data_ov004_02063ba8[align], y + 8, color, 0x209, text);
        func_01ff8710(screen->overlayLayer.buffer->pixels + 0x2e0, screen->textLayer.buffer->pixels, 0x5c0);
        return;
    }
    screen->textLayer.font = &work->fonts[fontIndex];
    DrawTextAnchored_020015a0(&screen->textLayer, data_ov004_02063ba8[align], y, color, 0x209, text);
}