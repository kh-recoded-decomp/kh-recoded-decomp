#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 pad_00[0xc];
    NNSG2dCharCanvas canvas;
} TextPage;

typedef struct {
    u8 pad_00[0x20];
    TextPage *currentPage;
} TextLayer;

void ClearTextArea_02001584(TextLayer *obj, int color, int x, int y, int width, int height)
{
    NNSG2dCharCanvas *canvas = &obj->currentPage->canvas;

    canvas->vtable->pClearArea(canvas, color, x, y, width, height);
}
