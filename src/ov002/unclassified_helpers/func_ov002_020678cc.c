#include "nitro/types.h"

extern u32 data_0205fe0c;
extern u32 func_ov002_0206985c(u32 target, u32 param);

void func_ov002_020678cc(u32 param, u32 *outValue) {
    u32 result = func_ov002_0206985c(data_0205fe0c + 0x2788, param);
    if (outValue != NULL) {
        *outValue = result;
    }
}
