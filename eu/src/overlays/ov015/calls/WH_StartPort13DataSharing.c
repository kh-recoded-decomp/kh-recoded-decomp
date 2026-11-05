#include "nitro/types.h"

extern u32 data_ov015_0207f3a0;
extern int WM_StartKeySharing(void *buffer, u32 size);
extern void WH_ChangeSysState(int id);
extern void WH_SetError(int error);

BOOL WH_StartPort13DataSharing(void) {
    int error;

    WH_ChangeSysState(6);
    error = WM_StartKeySharing(&data_ov015_0207f3a0, 0xd);
    if (error != 0) {
        WH_SetError(error);
        return 0;
    }
    return 1;
}
