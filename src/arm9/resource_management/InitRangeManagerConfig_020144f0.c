#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 param1;
    u32 param2;
    u32 param3;
    u32 param4;
} RangeManagerConfig2;

extern RangeManagerConfig2 g_rangeManagerConfig_0205a8e4;
extern void func_02014638(void);
extern void (*data_02055c4c)(void);
extern void (*data_02055c50)(void);
extern void func_02014548(void);
extern void func_020145cc(void);

void InitRangeManagerConfig_020144f0(u32 param1, u32 param2, u32 param3, u32 param4, int installCallbacks)
{
    g_rangeManagerConfig_0205a8e4.param1 = param1;
    g_rangeManagerConfig_0205a8e4.param2 = param2;
    g_rangeManagerConfig_0205a8e4.param3 = param3;
    g_rangeManagerConfig_0205a8e4.param4 = param4;
    func_02014638();

    if (installCallbacks != 0) {
        data_02055c4c = func_02014548;
        data_02055c50 = func_020145cc;
    }
}
