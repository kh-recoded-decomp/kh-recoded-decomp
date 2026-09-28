#include "nitro/types.h"

extern void func_ov001_0206c850(int obj);
extern void func_ov001_0206c720(u32 address);

void func_ov001_0206c994(int obj)
{
    int i;

    func_ov001_0206c850(obj + 4);
    i = 0;
    do {
        func_ov001_0206c850(obj + 0x2c + i * 0x28);
        i = i + 1;
    } while (i < 3);
    func_ov001_0206c720(0x206ca35);
}
