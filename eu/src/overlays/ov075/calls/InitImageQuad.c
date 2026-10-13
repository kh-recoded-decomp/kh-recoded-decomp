#include "src/overlays/MenuImageQuad.h"

ImageQuad *InitImageQuad(ImageQuad *quad, const MenuImage *image, s16 x, s16 y,
                        fx32 depth, u16 color)
{
    quad->image = image;
    quad->x = x;
    quad->y = y;
    quad->depth = depth;
    quad->texOffsetS = 0;
    quad->texOffsetT = 0;
    quad->width = image->width;
    quad->height = image->height;
    quad->color = color;
    return quad;
}
