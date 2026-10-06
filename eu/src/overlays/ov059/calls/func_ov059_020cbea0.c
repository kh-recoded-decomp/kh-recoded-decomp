#include "nitro/types.h"

extern u32 data_ov059_020cffc4;
extern u32 GaugePanel_Update;

void func_ov059_020cbea0(void) {
    ((void (*)(u32))&GaugePanel_Update)(data_ov059_020cffc4 + 5412);
}
