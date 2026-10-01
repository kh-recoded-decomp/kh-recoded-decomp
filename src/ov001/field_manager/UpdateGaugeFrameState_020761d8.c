#include "nitro/types.h"

typedef struct PartyGauge {
    u8 pad_000[0xfc];
    int state;
    int nextState;
    int paletteIndex;
    int frameCount;
} PartyGauge;

extern void func_ov001_020761a4(PartyGauge *gauge, s32 arg);
extern void func_ov001_02075d74(PartyGauge *gauge, int alternate);
extern BOOL func_ov001_02075db8(PartyGauge *gauge);

void UpdateGaugeFrameState_020761d8(PartyGauge *gauge, int stage)
{
    gauge->frameCount++;
    func_ov001_020761a4(gauge, stage);
    if (stage >= 3) {
        func_ov001_02075d74(gauge, 0);
        gauge->state = gauge->nextState;
        if (gauge->nextState == 2 && !func_ov001_02075db8(gauge)) {
            gauge->frameCount = 0;
            gauge->state = 0;
        }
    }
}
