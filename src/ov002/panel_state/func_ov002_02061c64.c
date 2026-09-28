#include "nitro/types.h"

typedef struct { s8 dx, dy; } TextDir;

extern u8 *g_panelState_0206c460;
extern void func_02017f10(int *ctx, int p2, int p3, int p4, int p5, int p6, int p7, int p8, TextDir dir);

void func_ov002_02061c64(int param1, int p2, int p3, int p4, int p5, int p6, int p7, int p8) {
    int newFlags;
    int self;
    int *fontChain;

    if (param1 == 0) {
        newFlags = (g_panelState_0206c460[0x11] & ~1) | 1;
        self = (int)g_panelState_0206c460 + 0xb0;
    } else {
        newFlags = g_panelState_0206c460[0x11] | 2;
        self = (int)g_panelState_0206c460 + 0xe4;
    }
    g_panelState_0206c460[0x11] = newFlags;

    TextDir dir = {0, 0};
    fontChain = *(int **)(self + 0x14);
    switch (*(u8 *)(*(int *)(*fontChain + 8) + 7)) {
    case 0:
    case 7:
        dir.dx = 1;
        break;
    case 1:
    case 2:
        dir.dy = 1;
        break;
    case 3:
    case 4:
        dir.dx = -1;
        break;
    case 5:
    case 6:
        dir.dy = -1;
        break;
    }
    func_02017f10((int *)(self + 0x10), p2, p3, p4, p5, p6, p7, p8, dir);
}
