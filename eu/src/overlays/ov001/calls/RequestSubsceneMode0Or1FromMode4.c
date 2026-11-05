#include "nitro/types.h"

extern u32 data_ov001_020a04e8;
extern s32 GetFieldSessionState(void);
extern u32 RequestPanelModeWithStyle2(BOOL flag);

u32 RequestSubsceneMode0Or1FromMode4(void)
{
    s32 mode;

    if (*(s32 *)(data_ov001_020a04e8 + 0xd8) != 4) {
        return 1;
    }
    mode = GetFieldSessionState();
    return RequestPanelModeWithStyle2(mode == 10);
}
