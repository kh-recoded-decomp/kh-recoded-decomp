#include "nitro/types.h"

typedef struct GaugeState {
    u8 pad_000[0x18];
    u32 tileBase;
    u8 pad_01c[0x30];
    s32 scale;
    u8 pad_050[0x76];
    u16 current;
    u16 maximum;
    u8 pad_0ca[0x42];
    u16 shownTotal;
    u16 shownTotalPrev;
    u8 pad_110[0x18];
    u16 drawnTotal;
    u16 drawnTotalPrev;
} GaugeState;

extern GaugeState *data_ov001_020a04ac;
extern void *GetSceneTagTracker_020711b0(void);
extern void DrawGaugeFill_020739d0(s32 fill, s32 rows);
extern void func_ov001_02073894(u32 tileBase, u32 row, s32 patternIndex);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void RefreshGaugeDisplay_0207421c(void)
{
    GaugeState *state = data_ov001_020a04ac;
    int current;
    void *pool;
    int divisor;
    int maximum;
    int total;
    int quotient;
    int fill;
    int rows;
    int i;

    pool = GetSceneTagTracker_020711b0();
    divisor = state->scale * 200;
    current = state->current * 0x30 / divisor;
    maximum = state->maximum;
    total = maximum * 0x30 / divisor;
    if (maximum != 0 && total == 0) {
        total = 1;
    }
    fill = 0x30;
    quotient = current / 0x30;
    if (total > quotient * 0x30 || total == 0) {
        fill = current - quotient * 0x30;
    }
    if (total > 0) {
        rows = (total - 1) % 0x30 + 1;
    } else {
        rows = 0;
    }
    DrawGaugeFill_020739d0(fill, rows);
    state->shownTotal = total;
    state->drawnTotal = state->shownTotal;
    state->shownTotalPrev = state->shownTotal;
    state->drawnTotalPrev = state->shownTotal;
    for (i = 0; i < rows; i++) {
        func_ov001_02073894(state->tileBase, i, 0);
    }
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 0x14));
}
