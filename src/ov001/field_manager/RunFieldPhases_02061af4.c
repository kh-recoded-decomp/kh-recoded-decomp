#include "nitro/types.h"

typedef int (*FieldPhaseFunc)(void);

typedef struct FieldState {
    u8 pad_000[0x1b];
    u8 rerun;
    int phase;
    u8 pad_020[0x214 - 0x20];
    u32 lowFlags : 8;
    u32 bgmActive : 1;
    u32 midFlags : 10;
    u32 bgmRequest : 1;
    u32 highFlags : 12;
} FieldState;

extern FieldState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern s32 func_ov001_02087868(s32 mode);
extern void UpdateFieldBgm_02062d1c(FieldState *field);
extern FieldPhaseFunc data_ov001_0209e680[];

int RunFieldPhases_02061af4(void)
{
    FieldState *field = NNSi_FndGetCurrentRootHeap_0202a764();
    int next;

    field->bgmActive = func_ov001_02087868(0) | field->bgmRequest;
    UpdateFieldBgm_02062d1c(field);
    do {
        field->rerun = FALSE;
        next = data_ov001_0209e680[field->phase]();
        if (next >= 0) {
            field->phase = next;
        }
    } while (field->rerun);
    if (field->phase == 13) {
        return -2;
    }
    return 0;
}
