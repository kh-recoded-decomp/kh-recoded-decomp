#include "nitro/types.h"

extern void func_02009b38(void);
extern void func_0200a0fc(void);
extern void func_02009bd0(int mode);
extern void func_02009434(void *request);
extern void *data_02056fe0;

void func_02009ddc(void) {
    func_02009b38();
    func_0200a0fc();
    func_02009bd0(8);
    *(u32 *)data_02056fe0 = 0;
    func_02009434(&data_02056fe0);
}
