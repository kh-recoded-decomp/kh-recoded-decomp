#include "nitro/types.h"

typedef struct PendingRequest {
    s32 unk_00;
    s32 handle;
    s32 active;
} PendingRequest;

typedef struct Manager {
    u8 pad_00[0x3c];
    PendingRequest request;
} Manager;

extern Manager *g_manager_020a0484;
extern void func_ov001_0207166c(void);

void ResetPendingRequest_0206c614(void)
{
    PendingRequest *request = &g_manager_020a0484->request;

    if (request->active == 1) {
        func_ov001_0207166c();
    }
    request->active = 0;
    request->handle = -1;
}
