#include "nitro/types.h"

extern int func_ov001_02067ed4(void);
extern int func_ov001_0206835c(int value);
extern int func_ov001_02069464(int slot);

int func_ov001_02069eb0(int slot)
{
    int result;

    *(u8 *)(slot + 0x10) = 0;
    result = func_ov001_02067ed4();
    if (*(char *)(slot + 0x12) != result) {
        return 0;
    }
    if ((*(char *)(slot + 0x14) == 0) &&
        (result = func_ov001_0206835c((int)*(short *)(slot + 0x16)), result != 0)) {
        *(u8 *)(slot + 0x10) = 1;
    }
    result = func_ov001_02069464(slot);
    if (result != 0) {
        return (int)*(char *)(slot + 0x10);
    }
    return 0;
}
