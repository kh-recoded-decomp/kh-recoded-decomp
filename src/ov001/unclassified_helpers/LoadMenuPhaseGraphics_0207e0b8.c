#include "nitro/types.h"

typedef struct {
    u8 pad0[0x10];
    int scroll;
    u8 pad14[4];
    u32 startTick;
    u8 pad1c[0x40 - 0x1c];
    u32 openGraphics;
    u32 idleGraphics;
    u32 closeGraphics;
} MenuContext;

extern MenuContext *data_ov001_020a04d0;
extern u32 func_0202a7a4(void);
extern void func_ov001_0207d800(MenuContext *context, u32 graphics);

void LoadMenuPhaseGraphics_0207e0b8(int phase, u32 graphics) {
    MenuContext *context = data_ov001_020a04d0;
    switch (phase) {
    case 0:
        context->startTick = func_0202a7a4();
        graphics = context->openGraphics;
        break;
    case 1:
        graphics = context->idleGraphics;
        break;
    case 2:
        graphics = context->closeGraphics;
        context->scroll -= 0x1e;
        break;
    }
    func_ov001_0207d800(context, graphics);
}
