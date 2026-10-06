#include "nitro/types.h"

extern u32 data_0205fe0c;
extern void SetRecordFlagFromTable(u32 target, u32 param1, u32 param2, u32 zero1, u32 zero2);

void func_ov002_020679ac(u32 param1, u32 param2) {
    SetRecordFlagFromTable(data_0205fe0c + 0x2788, param1, param2, 0, 0);
}
