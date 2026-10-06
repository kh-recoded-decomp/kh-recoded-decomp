#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 pad_0000[0x9c3c];
    u16 highlightColor;
} MenuWork;

extern int TextCanvas_GetLineWidth(NNSG2dTagCallbackInfo *info, const void *str, int stopAtTag);

void func_ov076_020cb154(u16 tag, NNSG2dTagCallbackInfo *info)
{
    MenuWork *work = info->cbParam;

    switch (tag) {
    case 1:
        info->clr = 0xf2;
        break;
    case 2:
        info->clr = work->highlightColor;
        break;
    case 4:
        info->clr = 0xfa;
        break;
    case 0x1f: {
        int areaWidth = info->txn.pCanvas->areaWidth * 8;
        int lineWidth = TextCanvas_GetLineWidth(info, info->str, 0);
        info->x = (areaWidth + 1) / 2 - (lineWidth + 1) / 2;
        info->y += info->txn.vSpace + info->txn.pFont->pRes->linefeed;
        break;
    }
    }
}
