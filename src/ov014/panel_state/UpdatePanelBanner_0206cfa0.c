#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0x4c];
    u8 recordPool[0xcf8d - 0x4c];
    s8 scrollStep;
    u8 pad_cf8e[2];
    s8 bannerMode;
    s8 bannerRows;
} PanelState;

typedef struct ScreenResource {
    u8 pad_00[8];
    void *screenData;
} ScreenResource;

typedef struct ScreenRecord {
    u8 pad_00[0x18];
    ScreenResource *resource;
} ScreenRecord;

extern PanelState *g_panelState_0206f9a0;
extern void *G2S_GetBG3ScrPtr_02007004(void);
extern void func_01ff8740(int value, void *dst, int size);
extern ScreenRecord *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void CopyClippedScreenRegion_020167d0(void *dst, void *screenData, int srcX, int srcY, int dstX, int dstY, int dstW, int dstH, int width, int height);

void UpdatePanelBanner_0206cfa0(void)
{
    ScreenRecord *record;
    void *screen;
    int rows;
    int step;
    u32 scroll;

    step = g_panelState_0206f9a0->scrollStep + 1;
    if (step >= 0x40) {
        step = 0;
    }
    g_panelState_0206f9a0->scrollStep = step;
    scroll = ((step >> 1) & 0x1ff) | (((step >> 1) << 16) & (0x1ff << 16));
    *(vu32 *)0x04000014 = scroll;
    *(vu32 *)0x04001014 = scroll;

    switch (g_panelState_0206f9a0->bannerMode) {
    case 0:
        break;
    case 2:
        g_panelState_0206f9a0->bannerRows -= 2;
    case 1:
        g_panelState_0206f9a0->bannerRows++;
        screen = G2S_GetBG3ScrPtr_02007004();
        func_01ff8740(0, (u8 *)screen + 0x40, 0x500);
        if (g_panelState_0206f9a0->bannerRows == 0) {
            return;
        }
        record = FindActiveRecordById_020b8184(g_panelState_0206f9a0->recordPool, 2);
        screen = G2S_GetBG3ScrPtr_02007004();
        CopyClippedScreenRegion_020167d0(screen, record->resource->screenData, 0, 0, 0xf, 1, 0x100, 0x100, 0x10, 1);
        rows = g_panelState_0206f9a0->bannerRows;
        screen = G2S_GetBG3ScrPtr_02007004();
        CopyClippedScreenRegion_020167d0(screen, record->resource->screenData, 0, 0x14 - rows, 0xf, 2, 0x100, 0x100, 0x10, rows + 1);
        return;
    case 3:
        record = FindActiveRecordById_020b8184(g_panelState_0206f9a0->recordPool, 3);
        screen = G2S_GetBG3ScrPtr_02007004();
        CopyClippedScreenRegion_020167d0(screen, record->resource->screenData, 0, 0, 0, 6, 0x100, 0x100, 0x20, 9);
        g_panelState_0206f9a0->bannerMode = 0;
        return;
    case 4:
        screen = G2S_GetBG3ScrPtr_02007004();
        func_01ff8740(0, (u8 *)screen + 0x180, 0x240);
        g_panelState_0206f9a0->bannerMode = 0;
        break;
    }
}
