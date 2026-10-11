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
    u8 pad_0000[0xc];
    Font font;
    TextLayer layers[6];
    TextFrame frames[6];
    u8 pad_01b0[0xcf1c - 0x1b0];
    PackedFileView views[4];
} MenuScene;

extern char data_ov093_020c4d40[];
extern const char *data_ov093_020c3e8c[];
extern int func_02001458(Font *font, const char *path);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern BOOL InitTextLayerDefault_02001494(TextLayer *layer, int bg, Font *font, TextFrame *frame);

static inline void SetTextFrame(TextFrame *frame, int x, int y, int width, int height, int charBase)
{
    frame->x = x;
    frame->y = y;
    frame->width = width;
    frame->height = height;
    frame->charBase = charBase;
    frame->palette = 0xf;
    frame->field_0c = 0;
    frame->lineSpacing = 2;
}

void InitEntryTextLayers_020bfac4(MenuScene *scene)
{
    int charBase;
    int i;
    TextFrame *frame;

    func_02001458(&scene->font, data_ov093_020c4d40);
    for (i = 0; i < 4; i++) {
        LoadPackedFileView_020ba25c(&scene->views[i], data_ov093_020c3e8c[i], FALSE);
    }
    charBase = 0x80;
    frame = &scene->frames[0];
    SetTextFrame(frame, 0x13, 0, 0xd, 2, charBase);
    InitTextLayerDefault_02001494(&scene->layers[0], 1, &scene->font, frame);
    charBase += frame->width * frame->height * 2;
    frame = &scene->frames[1];
    SetTextFrame(frame, 1, 0x12, 0xf, 2, charBase);
    InitTextLayerDefault_02001494(&scene->layers[1], 1, &scene->font, frame);
    charBase += frame->width * frame->height * 2;
    frame = &scene->frames[2];
    SetTextFrame(frame, 1, 0x14, 0x1e, 4, charBase);
    InitTextLayerDefault_02001494(&scene->layers[2], 1, &scene->font, frame);
    charBase = 0x40;
    frame = &scene->frames[3];
    SetTextFrame(frame, 3, 1, 0xf, 2, charBase);
    InitTextLayerDefault_02001494(&scene->layers[3], 5, &scene->font, frame);
    charBase += frame->width * frame->height;
    frame = &scene->frames[4];
    SetTextFrame(frame, 3, 4, 0x13, 0x12, charBase);
    InitTextLayerDefault_02001494(&scene->layers[4], 5, &scene->font, frame);
    charBase += frame->width * frame->height;
    frame = &scene->frames[5];
    SetTextFrame(frame, 0x17, 4, 4, 0x12, charBase);
    InitTextLayerDefault_02001494(&scene->layers[5], 5, &scene->font, frame);
}
