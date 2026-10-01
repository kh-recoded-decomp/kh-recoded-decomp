#include "nitro/types.h"

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

typedef struct GaugeScale {
    int unk0[3];
    int scale;
} GaugeScale;

extern GaugeContext *data_ov001_020a04ac;
extern GaugeScale data_ov001_0209edcc;
extern s64 SignedDivMod_02023dbc(int numerator, int denominator);
extern void func_ov001_020745e0(void);

void SetGaugeValues_02074688(int amount, int maximum) {
    GaugeContext *context = data_ov001_020a04ac;
    Gauge *lower = &context->gauges[0];
    Gauge *upper = &context->gauges[1];

    if (upper->active != 0) {
        upper->value = SignedDivMod_02023dbc(amount * data_ov001_0209edcc.scale, maximum);
    } else {
        upper->value = SignedDivMod_02023dbc(amount * data_ov001_0209edcc.scale, maximum);
        upper->shown = upper->value;
    }
    if (lower->active != 0) {
        lower->value = SignedDivMod_02023dbc(amount * data_ov001_0209edcc.scale, maximum);
    } else {
        lower->value = 0;
        lower->shown = lower->value;
    }
    func_ov001_020745e0();
}
