#include "nitro/types.h"

extern void func_02000f84(u32 arg0, u32 arg1, int arg2, int channel);

void InvokeForChannelOrBoth_0200110c(u32 arg0, u32 arg1, int arg2, int channel)
{
    if (channel < 0) {
        int i;

        for (i = 0; i < 2; i++) {
            func_02000f84(arg0, arg1, arg2, i);
        }
        return;
    }
    func_02000f84(arg0, arg1, arg2, channel);
}
