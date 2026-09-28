#include "nitro/types.h"
#include "nnsys/g2d.h"

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 8

typedef struct LC_INFO {
    const u8 *dst;
    const u8 *src;
    int ofs_x;
    int ofs_y;
    int width;
    int height;
    int dsrc;
    int srcBpp;
    int dstBpp;
    u32 cl;
} LC_INFO;

typedef union ObjSizeParam {
    u32 raw;
    struct {
        u32 widthShift : 8;
        u32 heightShift : 8;
        u32 reserved : 16;
    } shift;
} ObjSizeParam;

extern u32 G2D_GetCharIndex1D_02016cac(u32 charX, u32 charY, u32 areaWidth, u32 areaHeight, u32 objWidthShift, u32 objHeightShift);
extern void G2D_BlitGlyphTile_02016ec4(LC_INFO *i);

static inline int GetCharacterSize(const NNSG2dCharCanvas *pCC)
{
    return 8 * 8 * pCC->dstBpp / 8;
}

void G2D_DrawGlyph1D_0201728c(const NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, const NNSG2dGlyph *pGlyph)
{
    int ofs_x_base;
    int ofs_x;
    int ofs_y;
    int ofs_x_end;
    int ofs_y_end;
    u32 chara_x_base;
    u32 chara_x;
    u32 chara_y;
    u8 glyphWidth;
    u8 charHeight;
    int charSize;

    charSize = GetCharacterSize(pCC);

    {
        int chara_x_num;
        int chara_y_num;
        const unsigned int areaWidth = (unsigned int)pCC->areaWidth;
        const unsigned int areaHeight = (unsigned int)pCC->areaHeight;
        const NNSG2dCharWidths *const pWidth = pGlyph->pWidths;

        unsigned int chara_x_begin;
        unsigned int chara_x_last;
        unsigned int chara_y_begin;
        unsigned int chara_y_last;

        glyphWidth = pWidth->glyphWidth;
        charHeight = pFont->pRes->pGlyph->cellHeight;

        if (glyphWidth <= 0) {
            return;
        }

        if ((x + glyphWidth < 0) || (y + charHeight) < 0) {
            return;
        }

        chara_x_begin = (x <= 0) ? 0 : ((u32)x / CHARACTER_WIDTH);
        chara_y_begin = (y <= 0) ? 0 : ((u32)y / CHARACTER_HEIGHT);

        chara_x_last = (u32)(x + glyphWidth + (CHARACTER_WIDTH - 1)) / CHARACTER_WIDTH;
        if (chara_x_last >= areaWidth) {
            chara_x_last = areaWidth;
        }
        chara_y_last = (u32)(y + charHeight + (CHARACTER_HEIGHT - 1)) / CHARACTER_HEIGHT;
        if (chara_y_last >= areaHeight) {
            chara_y_last = areaHeight;
        }

        chara_x_num = (int)(chara_x_last - chara_x_begin);
        chara_y_num = (int)(chara_y_last - chara_y_begin);

        if ((chara_x_num < 0) || (chara_y_num < 0)) {
            return;
        }

        chara_x_base = chara_x_begin;
        chara_y = chara_y_begin;

        ofs_x_base = (x < 0) ? x : x & 0x7;
        ofs_y = (y < 0) ? y : y & 0x7;
        ofs_x_end = ofs_x_base - CHARACTER_WIDTH * chara_x_num;
        ofs_y_end = ofs_y - CHARACTER_HEIGHT * chara_y_num;
    }

    {
        LC_INFO i;
        u8 *charBase;
        u32 areaHeight;
        u32 areaWidth;
        ObjSizeParam objSize;
        u32 objHeightShift;
        u32 objWidthShift;

        i.src = pGlyph->image;
        i.width = glyphWidth;
        i.height = charHeight;
        i.cl = (u32)(cl - 1);
        i.srcBpp = pFont->pRes->pGlyph->bpp;
        i.dstBpp = pCC->dstBpp;
        i.dsrc = i.srcBpp * pFont->pRes->pGlyph->cellWidth;

        objSize.raw = pCC->param;
        areaWidth = (u32)pCC->areaWidth;
        charBase = pCC->charBase;
        areaHeight = (u32)pCC->areaHeight;
        objWidthShift = objSize.shift.widthShift;
        objHeightShift = objSize.shift.heightShift;

        for (; ofs_y > ofs_y_end; ofs_y -= CHARACTER_HEIGHT) {
            i.ofs_y = ofs_y;
            chara_x = chara_x_base;
            for (ofs_x = ofs_x_base; ofs_x > ofs_x_end; ofs_x -= CHARACTER_WIDTH) {
                const u32 charNo = G2D_GetCharIndex1D_02016cac(chara_x, chara_y, areaWidth, areaHeight, objWidthShift, objHeightShift);
                i.dst = charBase + charNo * charSize;
                i.ofs_x = ofs_x;
                G2D_BlitGlyphTile_02016ec4(&i);
                chara_x++;
            }
            chara_y++;
        }
    }
}
