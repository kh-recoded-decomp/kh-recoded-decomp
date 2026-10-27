#include "nitro/types.h"
#include "nnsys/g2d.h"

/* The text canvas starts after the layer's control fields. */
typedef struct TextLayerWidthView {
    u8 reserved00[0x10];
    NNSG2dTextCanvas canvas;
} TextLayerWidthView;

extern int GetLineWidth(const NNSG2dTextCanvas *canvas, const u16 *text, const u16 **nextLine);

int GetTextLayerLineWidth(const TextLayerWidthView *layer, const u16 *text, const u16 **nextLine)
{
    return GetLineWidth(&layer->canvas, text, nextLine);
}
