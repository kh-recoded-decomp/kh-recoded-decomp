#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 pad_08[4];
} TextFrame;

typedef struct {
    u8 pad_00[0x1c];
    TextLayer listLayer;
    TextLayer statsLayer;
    u8 pad_84[0x10];
    TextFrame statsFrame;
    u8 pad_a0[0x1e8 - 0xa0];
    u8 pad_1e8[0xc800];
    int messages[3];
    int values[5];
    u8 pad_ca08[0xcc7c - 0xca08];
    BOOL altLayout;
} MenuScene;

extern const char data_ov091_020c2c5c[];
extern const char data_ov091_020c2c68[];
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int color);
extern int func_020019f4(TextLayer *layer);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern void *func_ov027_020ba2a8(int *messages, int index);
extern void DrawShadowedAnchoredText_020bf724(TextLayer *layer, int x, int y, int color, int anchor, const void *text);
extern int func_0202e060(char *dst, const char *fmt, ...);

void DrawRecordSummaryText_020bf540(MenuScene *scene)
{
    int *messages = scene->messages;
    int lineHeight;
    int y;
    int i;
    int x;
    char firstText[20];
    char otherText[20];

    CallVirtualHandlerSlot1_02001574(&scene->listLayer, 0);
    y = 4;
    lineHeight = func_020019f4(&scene->listLayer);
    for (i = 0; i < 5; i++) {
        DrawShadowedAnchoredText_020bf724(&scene->listLayer, 8, y, 1, 0, func_ov027_020ba2a8(messages, i));
        y += lineHeight + 6;
    }
    Text_UploadTileBuffer_02001520(&scene->listLayer);

    CallVirtualHandlerSlot1_02001574(&scene->statsLayer, 0);
    x = (scene->statsFrame.width * 8) / 2;
    DrawShadowedAnchoredText_020bf724(&scene->statsLayer, x, 4, 3, 0x10, func_ov027_020ba2a8(messages, 6));
    y = 0x3e;
    lineHeight = func_020019f4(&scene->statsLayer);
    if (scene->altLayout) {
        y = 0x24;
    }
    for (i = 0; i < 5; i++) {
        DrawShadowedAnchoredText_020bf724(&scene->statsLayer, 0x1c, y, 1, 0, func_ov027_020ba2a8(messages, i));
        if (i == 0) {
            func_0202e060(firstText, data_ov091_020c2c5c, scene->values[i]);
            DrawShadowedAnchoredText_020bf724(&scene->statsLayer, 0x94, y, 1, 0x20, firstText);
        } else {
            func_0202e060(otherText, data_ov091_020c2c68, scene->values[i]);
            DrawShadowedAnchoredText_020bf724(&scene->statsLayer, 0x94, y, 1, 0x20, otherText);
        }
        y += lineHeight + 4;
    }
    if (scene->altLayout) {
        DrawShadowedAnchoredText_020bf724(&scene->statsLayer, 0x58, 0x74, 1, 0x10, func_ov027_020ba2a8(messages, 8));
    }
    Text_UploadTileBuffer_02001520(&scene->statsLayer);
}
