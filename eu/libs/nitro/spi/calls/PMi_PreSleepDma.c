#include "libs/nitro/mi/mi_dma_internal.h"

extern u32 PMi_PreDmaCnt[4];
extern void MI_WaitDma(u32 channel);
extern void MI_StopDma(u32 channel);

#define PM_CARD_ROM_CONTROL (*(volatile u32 *)0x040001a4)
#define PM_CARD_TRANSFER_BUSY 0x80000000
#define PM_DMA_REPEAT 0x02000000
#define PM_DMA_CONTROL(channel) \
    (*(vu32 *)(0x040000b8 + (channel) * MI_DMA_CHANNEL_STRIDE))

/* Save all DMA controls before sleep. Finish one-shot/display transfers,
 * wait for the card bus, and stop other repeating transfers. */
void PMi_PreSleepDma(void)
{
    u32 channel;
    u32 timing;

    for (channel = 0; channel <= MI_DMA_MAX_NUM; ++channel) {
        PMi_PreDmaCnt[channel] = PM_DMA_CONTROL(channel);
        timing = PM_DMA_CONTROL(channel) & MI_DMA_TIMING_ONLY_MASK;
        switch (timing) {
        case MI_DMA_TIMING_CARD:
            while (PM_CARD_ROM_CONTROL & PM_CARD_TRANSFER_BUSY) {
            }
            break;
        case MI_DMA_TIMING_DISP:
        case MI_DMA_TIMING_DISP_MMEM:
            MI_WaitDma(channel);
            break;
        default:
            if ((PM_DMA_CONTROL(channel) & PM_DMA_REPEAT) == 0) {
                MI_WaitDma(channel);
            } else {
                MI_StopDma(channel);
            }
            break;
        }
    }
}
