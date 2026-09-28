#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 param1;
    u32 param2;
    u32 param3;
} RangeManagerConfig;

extern RangeManagerConfig g_rangeManagerConfig_0205a900;
extern void func_020149c4(void);
extern void (*data_02055c54)(void);
extern void (*data_02055c58)(void);
extern void func_020148ac(void);
extern void func_02014980(void);

void InitRangeManagerConfig_02014858(u32 param1, u32 param2, u32 param3, int installCallbacks)
{
    g_rangeManagerConfig_0205a900.param1 = param1;
    g_rangeManagerConfig_0205a900.param2 = param2;
    g_rangeManagerConfig_0205a900.param3 = param3;
    func_020149c4();

    if (installCallbacks != 0) {
        data_02055c54 = func_020148ac;
        data_02055c58 = func_02014980;
    }
}
