#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextLayer TextLayer;
typedef struct TextFrame TextFrame;

extern BOOL InitTextLayer_020012c8(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame, BOOL fillMap, int alignFromEnd);

BOOL InitTextLayerDefault_02001494(TextLayer *obj, int layer, NNSG2dFont *font, TextFrame *frame)
{
    return InitTextLayer_020012c8(obj, layer, NULL, font, frame, TRUE, 0);
}
