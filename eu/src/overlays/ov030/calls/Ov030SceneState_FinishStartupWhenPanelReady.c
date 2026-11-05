#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 RequestSubsceneMode0Or1FromMode4(void);
extern void StoreToGlobalPtr4Field28(u32 value);

u32 Ov030SceneState_FinishStartupWhenPanelReady(void)
{
    s32 ready;

    ready = RequestSubsceneMode0Or1FromMode4();
    if (ready == 0) {
        return 0xffffffff;
    }
    if ((*(u16 *)(data_ov030_020bd020 + 6) & 1) != 0) {
        *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) & 0xfffe;
    }
    StoreToGlobalPtr4Field28(0);
    return 7;
}
