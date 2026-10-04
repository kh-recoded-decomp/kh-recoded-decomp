#include "nitro/types.h"

typedef struct {
    u8 pad[0x11148];
    int frameCounter;
    int blinkPhase;
} PanelWork;

typedef void (*PanelModeHandler)(PanelWork *work);

extern const PanelModeHandler data_ov095_020c16fc[];
extern int func_ov095_020c1208(PanelWork *work);
extern void InitSlotPool_020c01c8(PanelWork *work);
extern void func_ov095_020c0730(PanelWork *work);

void UpdatePanelFrame_020bedf8(PanelWork *work) {
    int mode = func_ov095_020c1208(work);

    if (data_ov095_020c16fc[mode] != NULL) {
        data_ov095_020c16fc[mode](work);
    }
    if (++work->frameCounter >= 8) {
        work->frameCounter = 0;
        work->blinkPhase = (work->blinkPhase + 1) % 2;
    }
    InitSlotPool_020c01c8(work);
    func_ov095_020c0730(work);
}