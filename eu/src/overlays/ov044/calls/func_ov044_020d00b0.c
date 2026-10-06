#include "nitro/types.h"

extern u32 data_ov044_020d0ec0;

extern void VEC_Subtract();
extern u32 func_ov044_020d00a0();
extern void SetSoundListenerFrame();

void func_ov044_020d00b0(BOOL shouldBlend)
{
    u32 panel;
    u8 blended[12];

    panel = data_ov044_020d0ec0;
    if ((*(u32 *)(data_ov044_020d0ec0 + 0x38) & 2) == 0) {
        if (shouldBlend) {
            VEC_Subtract(data_ov044_020d0ec0 + 0x14, data_ov044_020d0ec0 + 0x20, blended);
            SetSoundListenerFrame(panel + 0x20, blended, panel + 0x2c);
        }
        func_ov044_020d00a0(panel);
    }
}
