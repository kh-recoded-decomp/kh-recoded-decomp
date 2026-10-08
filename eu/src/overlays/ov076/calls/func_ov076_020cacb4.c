#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x602c];
    int isBusy;
} TextRenderer;

typedef struct {
    u8 pad_00000[8];
    int suppressCharUpload;
    u8 pad_0000c[0xc];
    TextRenderer *renderer;
    u8 pad_0001c[0x10];
    int isPaused;
    u8 pad_00030[0x4e38];
    u8 charBuffer[0x2400];
    u8 pad_07268[0xabf4];
    u32 frameParity;
} MenuWork;

extern MenuWork *gSlotMenuPanelWork;
extern u32 func_01ff80d4(void);
extern void *G2_GetBG1CharPtr(void);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void UpdateWidgetRootAndFireAlarm(TextRenderer *renderer, int mode);

void func_ov076_020cacb4(void)
{
    MenuWork *work = gSlotMenuPanelWork;

    if (work->isPaused != 0) {
        return;
    }
    if (((work->frameParity ^ func_01ff80d4()) & 1) != 0) {
        return;
    }
    if (work->suppressCharUpload == 0) {
        u8 *dest = (u8 *)G2_GetBG1CharPtr() + 0x140;
        MIi_CpuCopyFast(work->charBuffer, dest, sizeof(work->charBuffer));
    }
    if (work->renderer->isBusy == 0) {
        UpdateWidgetRootAndFireAlarm(work->renderer, 0);
    }
}
