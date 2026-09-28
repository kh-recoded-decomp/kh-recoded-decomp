#include "nitro/types.h"

extern u32 data_ov015_0207f3a0;
extern int func_02012270(void *buffer, u32 size);
extern void func_020737c4(int id);
extern void func_020737d4(int error);

BOOL func_ov015_02073c48(void) {
    int error;

    func_020737c4(6);
    error = func_02012270(&data_ov015_0207f3a0, 0xd);
    if (error != 0) {
        func_020737d4(error);
        return 0;
    }
    return 1;
}
