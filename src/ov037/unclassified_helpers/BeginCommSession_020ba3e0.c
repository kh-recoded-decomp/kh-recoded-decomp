#include "nitro/types.h"

typedef struct CommRequest {
    s8 slotIndex;
    s8 mode;
    s16 paramA;
    s16 paramB;
} CommRequest;

typedef struct CommState {
    s16 mode;
    s16 paramA;
    s16 paramB;
    u16 flags;
    s8 slotIndex;
    u8 pad_09[0x0b];
    s32 task;
    u8 pad_18[0x08];
    s32 counter;
} CommState;

extern CommState *g_commState_020bb760;
extern CommState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov037_020baa80(void);
extern s32 CreateOverlayTask_0206a6f4(int mode);
extern s32 func_ov037_020ba45c(void);

void *BeginCommSession_020ba3e0(CommRequest *request)
{
    g_commState_020bb760 = NNSi_FndGetCurrentRootHeap_0202a764();
    g_commState_020bb760->mode = request->mode;
    g_commState_020bb760->paramA = request->paramA;
    g_commState_020bb760->paramB = request->paramB;
    g_commState_020bb760->flags = 3;
    func_ov037_020baa80();
    g_commState_020bb760->task = CreateOverlayTask_0206a6f4(request->mode);
    g_commState_020bb760->slotIndex = request->slotIndex;
    g_commState_020bb760->counter = 0;
    return func_ov037_020ba45c;
}
