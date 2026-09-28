#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *callback;
} Registry;

typedef void (*Callback)(int, u32, u32, u32);

extern Registry data_02057620;
extern void func_02009b38(void);
extern void func_0200a0fc(void);
extern void func_02009bd0(int mode);
extern void *data_02056fe0;

void func_02009e80(int base) {
    Callback callback = (Callback)data_02057620.callback;
    u32 val500 = *(u32 *)(base + 0x500);
    u32 val4fc = *(u32 *)(base + 0x4fc);
    u32 val504 = *(u32 *)(base + 0x504);

    callback(0, val500, val4fc, val504);
    func_02009b38();
    func_0200a0fc();
    func_02009bd0(8);
    *(u32 *)data_02056fe0 = 0;
}
