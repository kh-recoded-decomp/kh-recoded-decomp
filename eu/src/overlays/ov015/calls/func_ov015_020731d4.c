#include "nitro/types.h"

extern int HasIdleActiveEntry(void);
extern void func_ov015_02072ee4(int state);
extern void WH_Finalize(void);
extern u8 *data_ov015_0207e964;

void func_ov015_020731d4(void) {
    int result;

    *(s16 *)(data_ov015_0207e964 + 0x7c) -= 1;
    if (*(s16 *)(data_ov015_0207e964 + 0x7c) > 0) {
        return;
    }
    result = HasIdleActiveEntry();
    if (result != 0) {
        return;
    }
    WH_Finalize();
    func_ov015_02072ee4(3);
}
