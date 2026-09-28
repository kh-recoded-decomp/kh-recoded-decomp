/* Measures the widest text line and total height using font line spacing plus caller-supplied horizontal and vertical spacing.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/g2d/calls/func_0201386c.c.
 * Original routine: func_0201386c. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




typedef struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} NNSG2dCharWidths;
typedef struct NNSG2dFontGlyph {
    u8 cellWidth;
    u8 cellHeight;
    u16 cellSize;
    s8 baselinePos;
    u8 maxCharWidth;
    u8 bpp;
    u8 flags;
    u8 glyphTable[];
} NNSG2dFontGlyph;
typedef struct NNSG2dFontWidth {
    u16 indexBegin;
    u16 indexEnd;
    struct NNSG2dFontWidth * pNext;
    NNSG2dCharWidths widthTable[];
} NNSG2dFontWidth;
typedef struct NNSG2dFontCodeMap {
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    struct NNSG2dFontCodeMap * pNext;
    u16 mapInfo[];
} NNSG2dFontCodeMap;
typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    NNSG2dFontGlyph * pGlyph;
    NNSG2dFontWidth * pWidth;
    NNSG2dFontCodeMap * pMap;
} NNSG2dFontInformation;
typedef u16 (*NNSiG2dSplitCharCallback)(const void ** ppChar);
typedef struct NNSG2dFont {
    NNSG2dFontInformation * pRes;
    NNSiG2dSplitCharCallback cbCharSpliter;
} NNSG2dFont;
typedef struct NNSG2dTextRect {
    int width;
    int height;
} NNSG2dTextRect;
inline s8 NNS_G2dFontGetLineFeed (const NNSG2dFont * pFont)
{
    return pFont->pRes->linefeed;
}
int func_02016aa0(const NNSG2dFont * pFont, int hSpace, const void * str, const void ** pPos);
extern int func_02016aa0 (const NNSG2dFont * pFont, int hSpace, const void * str, const void ** pPos);

/* G2D_MeasureTextRectangle_02016c18 -- NitroSystem g2d_Font.c: NNSi_G2dFontGetTextRect. */
NNSG2dTextRect G2D_MeasureTextRectangle_02016c18 (const NNSG2dFont * pFont, int hSpace, int vSpace, const void * txt)
{
    int lines = 1;
    NNSG2dTextRect rect = {0, 0};


    while (txt != NULL) {
        const int width = func_02016aa0(pFont, hSpace, txt, &txt);
        if (width > rect.width) {
            rect.width = width;
        }
        lines++;
    }

    rect.height = ((lines - 1) * (NNS_G2dFontGetLineFeed(pFont) + vSpace) - vSpace);

    return rect;
}
