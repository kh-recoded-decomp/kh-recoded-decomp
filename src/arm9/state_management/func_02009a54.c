#include "nitro/types.h"

extern void func_02004cf0(void);
extern void func_020099d4(u32 mask, u32 arg1, u32 arg2);
extern void func_02009738(int callback);
extern void func_02009344(u32 addr, u32 arg);

void func_02009a54(int callback) {
    if (callback == 0) {
        func_02004cf0();
    }
    func_020099d4(0, 0, 0);
    func_02009738(callback);
    func_02009344(0x20099a5, 0);
}
