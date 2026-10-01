#include "nitro/types.h"

typedef struct RequestState {
    int mode;
    s16 requestId;
} RequestState;

typedef struct Manager {
    u32 unk_00;
    RequestState state;
} Manager;

extern Manager *data_ov001_020a0484;
extern void ResetPendingRequest_0206c614(void);
extern void func_ov001_0206c528(int requestId);

void ResumeOrResetRequest_0206bbe4(int resume)
{
    RequestState *state = &data_ov001_020a0484->state;

    if (state->mode != 1 || resume == 0) {
        ResetPendingRequest_0206c614();
        return;
    }
    func_ov001_0206c528(state->requestId);
}
