#pragma opt_propagation off
#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} Font;

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 field_0c;
    u16 lineSpacing;
} TextFrame;

typedef struct {
    u8 data[0xc];
} PackedFileView;

typedef struct {
    u8 pad_0000[0x24];
    Font font;
    TextLayer layers[4];
    TextFrame frames[4];
    u8 pad_0140[0xcde4 - 0x140];
    PackedFileView views[3];
} MenuScene;

extern char data_ov097_020c24f4[];
extern const char *data_ov097_020c1dcc[];
extern int func_02001458(Font *font, const char *path);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern BOOL InitTextLayerDefault_02001494(TextLayer *layer, int bg, Font *font, TextFrame *frame);

void InitTextLayers_020bf93c(MenuScene *scene)
{
    int i;
    int size;
    int charBase;
    TextFrame *frame;
    TextFrame *next;

    func_02001458(&scene->font, data_ov097_020c24f4);
    i = 0;
    do {
        LoadPackedFileView_020ba25c(&scene->views[i], data_ov097_020c1dcc[i], FALSE);
    } while (++i < 3);
    charBase = 0x180;
    frame = &scene->frames[0];
    frame->width = 0xd;
    frame->height = 2;
    frame->x = 0x13;
    frame->y = 0;
    frame->charBase = charBase;
    frame->palette = 0xf;
    frame->field_0c = 0;
    frame->lineSpacing = 0;
    InitTextLayerDefault_02001494(&scene->layers[0], 5, &scene->font, frame);
    next = &scene->frames[1];
    next->x = 2;
    next->y = 4;
    next->width = 0xe;
    next->height = 0x12;
    next->charBase = charBase + frame->width * frame->height * 2;
    next->palette = 0xf;
    next->field_0c = 0;
    next->lineSpacing = 6;
    InitTextLayerDefault_02001494(&scene->layers[1], 5, &scene->font, next);
    frame = &scene->frames[2];
    frame->width = 0xf;
    frame->height = 2;
    frame->x = 3;
    frame->y = 1;
    frame->charBase = charBase;
    frame->palette = 0xf;
    frame->field_0c = 0;
    frame->lineSpacing = 0;
    InitTextLayerDefault_02001494(&scene->layers[2], 1, &scene->font, frame);
    size = frame->width * frame->height;
    next = &scene->frames[3];
    next->charBase = charBase + size * 2;
    next->y = 4;
    next->lineSpacing = 6;
    next->x = 2;
    next->width = 0x1a;
    next->height = 0x12;
    next->palette = 0xf;
    next->field_0c = 0;
    InitTextLayerDefault_02001494(&scene->layers[3], 1, &scene->font, next);
}
