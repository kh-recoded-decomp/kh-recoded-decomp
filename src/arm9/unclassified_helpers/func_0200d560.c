#include "nitro/types.h"

extern u32 data_02057b80;
extern void func_0200d3bc(int priority);
extern void func_0200b75c(void);

void func_0200d560(int priority)
{
    if (data_02057b80 == 0) {
        data_02057b80 = 1;
        func_0200d3bc(priority);
        func_0200b75c();
    }
}
