#include "nitro/types.h"

extern u32 data_ov059_020cffc4;
extern u32 GaugePanel_Update;

void UpdateGlobalActorGaugePanel(void) {
    ((void (*)(u32))&GaugePanel_Update)(data_ov059_020cffc4 + 5412);
}
