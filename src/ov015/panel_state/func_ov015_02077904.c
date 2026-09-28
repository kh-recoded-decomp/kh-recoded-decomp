#include "nitro/types.h"

extern void func_0204d924(int a, int b);
extern s8 *data_ov015_020812e0;

void func_ov015_02077904(void) {
    if (data_ov015_020812e0[0x5f] != 0) {
        return;
    }
    func_0204d924(2, 0xc);
    data_ov015_020812e0[0x5f] = 1;
}
