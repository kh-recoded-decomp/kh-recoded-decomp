#include "nitro/types.h"

extern void func_02005274(int channel);

void ResetFourChannels_020052dc(void) {
    func_02005274(0);
    func_02005274(1);
    func_02005274(2);
    func_02005274(3);
}
