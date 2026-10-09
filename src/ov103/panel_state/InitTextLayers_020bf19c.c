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
    u8 pad_0000[0x18];
    Font font;
    TextLayer layers[4];
    TextFrame frames[4];
    u8 pad_0134[0xcb64 - 0x134];
    PackedFileView views[3];
} Ov103State;

extern char data_ov103_020c06d8[];
extern const char *data_ov103_020c04a8[];
extern int func_02001458(Font *font, const char *path);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern BOOL InitTextLayerDefault_02001494(TextLayer *layer, int bg, Font *font, TextFrame *frame);

void InitTextLayers_020bf19c(Ov103State *state)
{
    int i;
    int size;
    int charBase;
    TextFrame *frame;
    TextFrame *next;

    func_02001458(&state->font, data_ov103_020c06d8);
    i = 0;
    do {
        LoadPackedFileView_020ba25c(&state->views[i], data_ov103_020c04a8[i], FALSE);
    } while (++i < 3);
    charBase = 0x80;
    frame = &state->frames[0];
    frame->x = 0x10;
    frame->y = 0;
    frame->width = 0x10;
    frame->height = 2;
    frame->charBase = charBase;
    frame->palette = 0xf;
    frame->field_0c = 0;
    frame->lineSpacing = 2;
    InitTextLayerDefault_02001494(&state->layers[0], 1, &state->font, frame);
    next = &state->frames[3];
    next->x = 3;
    next->y = 4;
    next->width = 0x1a;
    next->height = 0x12;
    next->charBase = charBase + frame->width * frame->height * 2;
    next->palette = 0xf;
    next->field_0c = 0;
    next->lineSpacing = 2;
    InitTextLayerDefault_02001494(&state->layers[3], 1, &state->font, next);
    charBase = 0x200;
    frame = &state->frames[1];
    frame->x = 1;
    frame->y = 2;
    frame->width = 0x1f;
    frame->height = 2;
    frame->charBase = charBase;
    frame->palette = 0xf;
    frame->field_0c = 0;
    frame->lineSpacing = 2;
    InitTextLayerDefault_02001494(&state->layers[1], 5, &state->font, frame);
    size = frame->width * frame->height;
    next = &state->frames[2];
    next->x = 6;
    next->y = 4;
    next->width = 0x14;
    next->height = 5;
    next->charBase = charBase + size * 2;
    next->palette = 0xf;
    next->field_0c = 0;
    next->lineSpacing = 2;
    InitTextLayerDefault_02001494(&state->layers[2], 5, &state->font, next);
}
