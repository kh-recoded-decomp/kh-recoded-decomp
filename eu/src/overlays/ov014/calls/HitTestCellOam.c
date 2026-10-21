#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;

typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData *pOamAttrArray;
} NNSG2dCellData;

/* NitroSDK's GXOamAttr: the bitfields overlay the three attribute halfwords. */
typedef union GXOamAttr {
    u16 attr[4];
    struct {
        u32 y : 8;
        u32 rsMode : 2;
        u32 objMode : 2;
        u32 mosaic : 1;
        u32 colorMode : 1;
        u32 shape : 2;
        u32 x : 9;
        u32 rsParam : 3;
        u32 flipH : 1;
        u32 flipV : 1;
        u32 size : 2;
        u32 charNo : 10;
        u32 priority : 2;
        u32 cParam : 4;
        u32 _3 : 16;
    };
    struct {
        u32 attr01;
        u16 attr2;
        u16 attr3;
    };
} GXOamAttr;

extern const u16 NNSi_objSizeWTbl[3][4];
extern const u16 NNSi_objSizeHTbl[3][4];

typedef int GXOamShape;

#define HW_OBJ_VRAM_SUB 0x06600000
#define GX_OAM_ATTR01_SHAPE_MASK 0x0000c000
#define GX_OAM_ATTR01_SHAPE_SHIFT 14
#define GX_OAM_ATTR01_SIZE_MASK 0xc0000000
#define GX_OAM_ATTR01_SIZE_SHIFT 30

static inline void NNS_G2dCopyCellAsOamAttr(const NNSG2dCellData *cell, u16 index, GXOamAttr *dst)
{
    dst->attr[0] = cell->pOamAttrArray[index].attr0;
    dst->attr[1] = cell->pOamAttrArray[index].attr1;
    dst->attr[2] = cell->pOamAttrArray[index].attr2;
}

static inline GXOamShape NNS_G2dGetOAMSize(const GXOamAttr *oam)
{
    return (GXOamShape)(oam->attr01 & (GX_OAM_ATTR01_SHAPE_MASK | GX_OAM_ATTR01_SIZE_MASK));
}

static inline int NNS_G2dGetOamSizeX(const GXOamShape *shape)
{
    return NNSi_objSizeWTbl[(*shape & GX_OAM_ATTR01_SHAPE_MASK) >> GX_OAM_ATTR01_SHAPE_SHIFT]
                           [(*shape & GX_OAM_ATTR01_SIZE_MASK) >> GX_OAM_ATTR01_SIZE_SHIFT];
}

static inline int NNS_G2dGetOamSizeY(const GXOamShape *shape)
{
    return NNSi_objSizeHTbl[(*shape & GX_OAM_ATTR01_SHAPE_MASK) >> GX_OAM_ATTR01_SHAPE_SHIFT]
                           [(*shape & GX_OAM_ATTR01_SIZE_MASK) >> GX_OAM_ATTR01_SIZE_SHIFT];
}

/*
 * Whether the screen point (x, y) lands on an opaque pixel of OAM `index` of a cell drawn at
 * `pos`, reading the 8x8 character tiles of the sub-screen OBJ VRAM.
 */
BOOL HitTestCellOam(const NNSG2dCellData *cell, u16 index, int charBase, const VecFx32 *pos, int x, int y)
{
    GXOamAttr oam;
    GXOamShape shape;
    BOOL hit;
    int left;
    int top;
    int width;
    int height;
    int px;
    int py;
    int originX;
    int originY;

    originX = (pos->x + 0x800) >> 12;
    originY = (pos->y + 0x800) >> 12;
    NNS_G2dCopyCellAsOamAttr(cell, index, &oam);
    hit = FALSE;
    /* The OAM x is a signed 9-bit value and y a signed 8-bit one. */
    left = oam.x;
    if (left > 0xff) {
        left |= ~0xff;
    }
    left += originX;
    top = oam.y;
    if (top > 0x7f) {
        top |= ~0x7f;
    }
    top += originY;

    shape = NNS_G2dGetOAMSize(&oam);
    width = NNS_G2dGetOamSizeX(&shape);
    height = NNS_G2dGetOamSizeY(&shape);
    if (left <= x && x < left + width && top <= y && y < top + height) {
        px = x - left;
        py = y - top;
        if (oam.flipH) {
            px = width - 1 - px;
        }
        if (oam.flipV) {
            py = height - 1 - py;
        }
        if (((u8 *)(HW_OBJ_VRAM_SUB + ((u16)(charBase + oam.charNo) << 7) +
                    ((py >> 3) * width / 8 + (px >> 3)) * 64))[(px & 7) + (py & 7) * 8] != 0) {
            hit = TRUE;
        }
    }
    return hit;
}
