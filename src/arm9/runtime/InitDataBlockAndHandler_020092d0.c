#include "nitro/types.h"

extern void *data_02056fe0;
extern u8 data_02056f80[0x60];
extern void func_01ff8740(int mode, void *ptr, int size);
extern void func_0200344c(void *ptr, int size);
extern void func_0200e29c(int id, u32 addr);

void InitDataBlockAndHandler_020092d0(void) {
    data_02056fe0 = &data_02056f80;
    func_01ff8740(0, &data_02056f80, 0x60);
    func_0200344c(&data_02056f80, 0x60);
    func_0200e29c(0xb, 0x20094e5);
}
