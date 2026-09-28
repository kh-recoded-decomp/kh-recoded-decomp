#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u32 func_ov001_02062c98();
extern u32 func_ov001_02062cd4();
extern u32 func_ov001_020630e4();

u32 func_ov001_02062654(void) {
    u32 value = data_ov001_020a0460;
    func_ov001_02062c98(data_ov001_020a0460, 1);
    func_ov001_02062cd4(value);
    func_ov001_020630e4();
    return 4;
}
