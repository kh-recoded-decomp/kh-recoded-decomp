#include "nitro/types.h"

extern u32 data_0205fe0c;
extern u32 MarkRecordFlagBits(u32 target, u32 param);

void func_ov002_020678cc(u32 param, u32 *outValue) {
    u32 result = MarkRecordFlagBits(data_0205fe0c + 0x2788, param);
    if (outValue != NULL) {
        *outValue = result;
    }
}
