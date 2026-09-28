#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int func_ov001_02063620(void);
extern void func_020365a4(void);
extern void func_ov035_020baa28(void);
extern void func_ov035_020bab2c(void);
extern void func_ov035_020bb4a4(int width, int height, u8 mode);

u32 func_ov035_020ba574(void) {
    if (func_ov001_02063620() != 0) {
        return 0xffffffff;
    }
    func_020365a4();
    func_ov035_020baa28();
    func_ov035_020bab2c();
    func_ov035_020bb4a4((int)*(s16 *)(data_ov035_020bc4e0 + 0x46),
                        (int)*(s16 *)(data_ov035_020bc4e0 + 0x48),
                        *(u8 *)(data_ov035_020bc4e0 + 0x42));
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x8000;
    return 1;
}
