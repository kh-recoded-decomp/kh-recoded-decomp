#include "nitro/types.h"

typedef int (*SessionUpdateFunc)(void);

extern void *data_ov000_02063a08;
extern char OverlayId39_00000027[];

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02029f78(int processor, int overlayId);
extern void InitOverlayState_020bb888(u32 entryArg);
extern void func_ov039_020bcd68(int selection);
extern int func_ov000_020636ec(void);

SessionUpdateFunc EnterOv039Selection_02063680(int selection)
{
    data_ov000_02063a08 = NNSi_FndGetCurrentRootHeap_0202a764();
    func_02029f78(0, (int)OverlayId39_00000027);
    InitOverlayState_020bb888(8);
    func_ov039_020bcd68(selection);
    return func_ov000_020636ec;
}
