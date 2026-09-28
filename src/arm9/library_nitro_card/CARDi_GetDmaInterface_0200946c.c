#include "nitro/types.h"

typedef struct CardDmaInterface {
    void (*copy)(u32 channel, const void *src, void *dst, u32 length);
    void (*stop)(u32 channel);
} CardDmaInterface;

extern const CardDmaInterface data_02052964;
extern void OS_Terminate_02004cf0(void);

#pragma opt_propagation off
const CardDmaInterface *CARDi_GetDmaInterface_0200946c(u32 channel)
{
    const CardDmaInterface *dmaInterface = NULL;
    BOOL isNewDma = (channel & 0x10) ? TRUE : FALSE;

    channel &= ~0x10;
    if (channel <= 3) {
        if (!isNewDma) {
            dmaInterface = &data_02052964;
        } else {
            OS_Terminate_02004cf0();
        }
    }
    return dmaInterface;
}
#pragma opt_propagation reset
