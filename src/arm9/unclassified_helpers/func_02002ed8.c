#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 flags;
} StatusBlock_02055bd0;

extern StatusBlock_02055bd0 data_02055bd0;
extern u32 func_02002f0c(void);

void func_02002ed8(void)
{
    if (data_02055bd0.flags != (u32)-1) {
        return;
    }
    data_02055bd0.flags = 0x80000001;
    data_02055bd0.flags = data_02055bd0.flags | func_02002f0c();
}
