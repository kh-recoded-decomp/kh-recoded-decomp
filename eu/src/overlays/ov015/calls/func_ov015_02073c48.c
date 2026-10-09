#include "nitro/types.h"

extern u32 data_ov015_0207f3a0;
extern int func_02012284(void *buffer, u32 size);
extern void WH_ChangeSysState(int id);
extern void WH_SetError(int error);

BOOL func_ov015_02073c48(void) {
    int error;

    WH_ChangeSysState(6);
    error = func_02012284(&data_ov015_0207f3a0, 0xd);
    if (error != 0) {
        WH_SetError(error);
        return 0;
    }
    return 1;
}
