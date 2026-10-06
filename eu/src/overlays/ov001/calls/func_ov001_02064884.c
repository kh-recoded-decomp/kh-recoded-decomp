#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x218];
    u32 pendingValue;
} Session;

extern Session *data_ov001_020a0480;
extern void ConfigureFieldTracks(int x, int y, int mode, int param);
extern u32 func_ov001_0206dc4c(int index);
extern u32 GetBiasAdjustedField(int index);
extern void func_ov001_020645f4(u32 values, u32 extra);
extern void SetGlobalStateValue(u32 value);

void func_ov001_02064884(u32 value)
{
    u32 values;

    ConfigureFieldTracks(900, -4, 1, -1);
    data_ov001_020a0480->pendingValue = value;
    values = func_ov001_0206dc4c(0);
    func_ov001_020645f4(values, GetBiasAdjustedField(0));
    SetGlobalStateValue(-1);
}
