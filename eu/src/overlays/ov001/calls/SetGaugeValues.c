#include "nitro/types.h"
#include "src/overlays/ov001/HudGaugeTable.h"

/* Shared implementation: src/ov001/shared_engine/SetGaugeValues_02074688.c. */

typedef struct Gauge {
    u16 unk0;
    u16 shown;
    u16 value;
    u8 pad6[0x12];
    int active;
} Gauge;

typedef struct GaugeContext {
    u8 pad[0xd4];
    Gauge gauges[2];
} GaugeContext;

extern GaugeContext *data_ov001_020a04cc;
extern s64 _s32_div_f(int numerator, int denominator);
extern void RedrawHudGaugeRows(void);

void SetGaugeValues(int amount, int maximum) {
    GaugeContext *context = data_ov001_020a04cc;
    Gauge *lower = &context->gauges[0];
    Gauge *upper = &context->gauges[1];

    if (upper->active != 0) {
        upper->value = _s32_div_f(amount * gHudGaugeTable.layouts[0].cellCount, maximum);
    } else {
        upper->value = _s32_div_f(amount * gHudGaugeTable.layouts[0].cellCount, maximum);
        upper->shown = upper->value;
    }
    if (lower->active != 0) {
        lower->value = _s32_div_f(amount * gHudGaugeTable.layouts[0].cellCount, maximum);
    } else {
        lower->value = 0;
        lower->shown = lower->value;
    }
    RedrawHudGaugeRows();
}
