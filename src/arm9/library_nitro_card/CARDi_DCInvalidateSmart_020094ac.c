#include "nitro/types.h"

extern void DC_FlushAll_020033e0(void);
extern void DC_StoreRange_02003430(void *address, u32 length);
extern void DC_InvalidateRange_02003414(void *address, u32 length);
extern void DC_WaitWriteBufferEmpty_02003470(void);

void CARDi_DCInvalidateSmart_020094ac(void *buffer, u32 length, u32 threshold)
{
    if (length >= threshold) {
        DC_FlushAll_020033e0();
    } else {
        u32 position = (u32)buffer;
        u32 misalign = position & 0x1f;

        if (misalign) {
            position -= misalign;
            DC_StoreRange_02003430((void *)position, 0x20);
            DC_StoreRange_02003430((void *)(position + length), 0x20);
            length += 0x20;
        }
        DC_InvalidateRange_02003414((void *)position, length);
        DC_WaitWriteBufferEmpty_02003470();
    }
}
