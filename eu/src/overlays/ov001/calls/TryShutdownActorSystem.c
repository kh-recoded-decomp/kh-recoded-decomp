#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x3EE0];
    void *releasableHandle;
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern void ZeroHalfThenFree(void *block);
extern void PopVramState(void);
extern void func_ov001_0206375c(void);
extern s32 func_ov001_02063a38(void);
extern s32 IsSessionFlagSet(s32 id);
extern void ClearSessionPackedBit(s32 id);
extern void func_ov001_0206e444(s32 flag);
extern s32 IsFieldPanelHidden(void);
extern void ClearAllActorSlots(void);
extern s32 IsTransitionStateDone(void);
extern void FinishEventCameraCut(void);
extern void func_ov040_020bdba4(void);

s32 TryShutdownActorSystem(void)
{
    ActorManager *manager;
    s32 result;
    s32 sessionMode;

    manager = data_ov001_020a0500;
    result = IsFieldPanelHidden();
    if (result != 0 && (result = IsTransitionStateDone(), result != 0)) {
        FinishEventCameraCut();
        PopVramState();
        ClearAllActorSlots();
        func_ov001_0206375c();
        func_ov001_0206e444(1);
        ZeroHalfThenFree(manager->releasableHandle);
        manager->releasableHandle = 0;
        sessionMode = func_ov001_02063a38();
        if (sessionMode == 6 && (sessionMode = IsSessionFlagSet(0x3628), sessionMode != 0) &&
            (sessionMode = IsSessionFlagSet(0x363c), sessionMode == 0)) {
            ClearSessionPackedBit(0x3628);
            func_ov040_020bdba4();
        }
        return 0x20882d5;
    }
    return 0;
}
