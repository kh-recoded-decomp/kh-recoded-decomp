#include "nitro/types.h"

extern void func_0201057c(void);
extern void func_0200a12c(int a, int b);
extern void func_020052dc(void);
extern void func_02004cf0(void);

void func_0200a0d0(void) {
    if ((*(vu16 *)0x02ffffa8 & 0x8000) >> 15) {
        func_0201057c();
    }
    func_0200a12c(1, 1);
    func_020052dc();
    func_02004cf0();
}
