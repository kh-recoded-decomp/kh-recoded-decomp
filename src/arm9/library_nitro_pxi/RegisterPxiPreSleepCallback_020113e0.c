#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;
struct PMSleepCallbackInfo {
    void (*callback)(void *arg);
    void *arg;
    u32 pad_08;
    PMSleepCallbackInfo *next;
};

typedef struct {
    u32 pad_00;
    u32 pad_04;
    PMSleepCallbackInfo preSleepCallback;
} PxiState;

extern PxiState data_020597fc;
extern void *PXI_Init_02011414(void);
extern void PMi_InsertPreSleepCallback_02010aec(PMSleepCallbackInfo *info, int priority);

void RegisterPxiPreSleepCallback_020113e0(void)
{
    data_020597fc.preSleepCallback.callback = (void (*)(void *))PXI_Init_02011414;
    data_020597fc.preSleepCallback.arg = NULL;
    PMi_InsertPreSleepCallback_02010aec(&data_020597fc.preSleepCallback, 1000);
}
