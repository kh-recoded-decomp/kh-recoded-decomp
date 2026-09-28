#include "nitro/types.h"

extern void PXI_Init_0200e1ec(void);
extern void func_0200e29c(int id, u32 addr);
extern int data_020578e0;

void func_0200a04c(void) {
    int *state = &data_020578e0;

    PXI_Init_0200e1ec();
    state[0] = 0;
    state[1] = 0;
    func_0200e29c(0xe, 0x200a071);
    state[2] = 0;
}
