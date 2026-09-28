#include "nitro/types.h"
#include "nnsys/g2d.h"

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 8
#define MATH_ROUNDUP(x, base) (((x) + ((base) - 1)) & ~((base) - 1))
#define MATH_ROUNDDOWN(x, base) ((x) & ~((base) - 1))

typedef union ObjSizeParam {
    u32 raw;
    struct {
        u32 widthShift : 8;
        u32 heightShift : 8;
        u32 reserved : 16;
    } shift;
} ObjSizeParam;

extern u32 G2D_GetCharIndex1D_02016cac(u32 charX, u32 charY, u32 areaWidth, u32 areaHeight, u32 objWidthShift, u32 objHeightShift);
extern void G2D_FillCharacterRectangle_02016d94(void *pChar, int x, int y, int w, int h, u32 cl8, int bpp);

static inline int GetCharacterSize(const NNSG2dCharCanvas *pCC)
{
    return 8 * 8 * pCC->dstBpp / 8;
}

static inline u32 SpreadColor32(const NNSG2dCharCanvas *pCC, int cl)
{
    u32 val = (u32)cl;
    if (pCC->dstBpp == 4) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }
    return val;
}

void G2D_ClearArea1D_020176fc(const NNSG2dCharCanvas *pCC, int cl, int x, int y, int w, int h)
{
    int ix, iy;
    int cx, cy, cw, ch;
    u32 chara_x;
    const int xw = x + w;
    const int yh = y + h;
    u32 cl8;

    cl8 = SpreadColor32(pCC, cl);

    {
        const int left = MATH_ROUNDDOWN(x, CHARACTER_WIDTH);
        const int top = MATH_ROUNDDOWN(y, CHARACTER_HEIGHT);
        const int right = MATH_ROUNDUP(xw, CHARACTER_WIDTH);
        const int bottom = MATH_ROUNDUP(yh, CHARACTER_HEIGHT);
        const int charSize = GetCharacterSize(pCC);
        const int bpp = pCC->dstBpp;
        const u32 chara_x_base = (u32)(left / CHARACTER_WIDTH);
        u32 chara_y = (u32)(top / CHARACTER_HEIGHT);
        const u32 areaWidth = (u32)pCC->areaWidth;
        const u32 areaHeight = (u32)pCC->areaHeight;
        u8 *const charBase = pCC->charBase;
        ObjSizeParam objSize;

        objSize.raw = pCC->param;
        const u32 objWidthShift = objSize.shift.widthShift;
        const u32 objHeightShift = objSize.shift.heightShift;

        for (iy = top; iy < bottom; iy += CHARACTER_HEIGHT) {
            cy = (iy < y) ? y - iy : 0;
            ch = ((yh - iy > CHARACTER_HEIGHT) ? CHARACTER_HEIGHT : yh - iy) - cy;
            chara_x = chara_x_base;

            for (ix = left; ix < right; ix += CHARACTER_WIDTH) {
                const u32 charNo = G2D_GetCharIndex1D_02016cac(chara_x, chara_y, areaWidth, areaHeight, objWidthShift, objHeightShift);
                cx = (ix < x) ? x - ix : 0;
                cw = ((xw - ix > CHARACTER_WIDTH) ? CHARACTER_WIDTH : xw - ix) - cx;

                G2D_FillCharacterRectangle_02016d94(charBase + charNo * charSize, cx, cy, cw, ch, cl8, bpp);
                chara_x++;
            }
            chara_y++;
        }
    }
}
