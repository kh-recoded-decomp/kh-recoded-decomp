#include "nitro/types.h"

extern int func_ov015_0206fa38(void);
extern void func_ov015_02072ee4(int state);
extern void func_ov015_02074ec8(void);
extern u8 *data_ov015_0207e964;

void func_ov015_02073238(void) {
    int result;

    *(s16 *)(data_ov015_0207e964 + 0x7c) -= 1;
    if (*(s16 *)(data_ov015_0207e964 + 0x7c) > 0) {
        return;
    }
    result = func_ov015_0206fa38();
    if (result != 0) {
        return;
    }
    func_ov015_02074ec8();
    func_ov015_02072ee4(3);
}
