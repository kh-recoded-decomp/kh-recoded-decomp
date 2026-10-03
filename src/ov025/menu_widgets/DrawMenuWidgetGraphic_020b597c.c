#include "nitro/types.h"

typedef struct ScreenGraphic {
    u8 pad_00[8];
    void *screenData;
} ScreenGraphic;

typedef struct MenuWidget {
    u16 unk_0;
    s16 dstX;
    s16 dstY;
    u16 srcX;
    u16 srcY;
    u8 pad_0a[6];
    int type;
    u8 pad_14[4];
    ScreenGraphic *graphic;
} MenuWidget;

extern u32 _data_ov025_020b7760;
extern void *G2S_GetBG1ScrPtr_02006e68(void);
extern void CopyClippedScreenRegion_020167d0(void *screenDst, void *screenData, int srcX, int srcY, int dstX, int dstY,
                                             int dstW, int dstH, int width, int height);
extern void func_ov027_020b9a74(u32 owner, MenuWidget *widget);

void DrawMenuWidgetGraphic_020b597c(MenuWidget *widget)
{
    switch (widget->type) {
    case 0x19:
        CopyClippedScreenRegion_020167d0(G2S_GetBG1ScrPtr_02006e68(), widget->graphic->screenData, widget->srcX,
                                         widget->srcY, widget->dstX, widget->dstY, 32, 32, 32, 32);
        break;
    case 0x1a:
    case 0x1b:
        func_ov027_020b9a74(_data_ov025_020b7760 + 0x64c8, widget);
        break;
    }
}
