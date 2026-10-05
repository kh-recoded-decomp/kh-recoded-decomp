#include "nitro/types.h"

typedef struct WorldSession {
    s32 field0;
    s32 field4;
} WorldSession;

typedef int (*SessionUpdateFunc)(void);

extern WorldSession *data_02063a04;
extern char OverlayId27_0000001b[];
extern char OverlayId39_00000027[];

extern WorldSession *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02029f78(int processor, int overlayId);
extern void InitOverlayState_020bb888(u32 entryArg);
extern int NotifyOv039OfWorld_02063614(void);

SessionUpdateFunc EnterWorldSession_02063578(void)
{
    WorldSession *session = NNSi_FndGetCurrentRootHeap_0202a764();

    data_02063a04 = session;
    func_02029f78(0, (int)OverlayId27_0000001b);
    func_02029f78(0, (int)OverlayId39_00000027);
    session->field0 = -1;
    session->field4 = 0;
    InitOverlayState_020bb888(3);
    return NotifyOv039OfWorld_02063614;
}
