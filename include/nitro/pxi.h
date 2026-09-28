/* PXI: the FIFO between the ARM9 and the ARM7, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_PXI_H
#define NITRO_PXI_H

#include "nitro/types.h"


typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;

typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);

typedef s32 PXIProc;

typedef enum {
    PXI_FIFO_SUCCESS = 0,
    PXI_FIFO_FAIL_SEND_ERR = -1,
    PXI_FIFO_FAIL_SEND_FULL = -2,
    PXI_FIFO_FAIL_RECV_ERR = -3,
    PXI_FIFO_FAIL_RECV_EMPTY = -4,
    PXI_FIFO_NO_CALLBACK_ENTRY = -5
} PXIFifoStatus;

#define PXI_FIFOMESSAGE_BITSZ_TAG   5

#define PXI_FIFOMESSAGE_BITSZ_ERR   1

#define PXI_FIFOMESSAGE_BITSZ_DATA  26

typedef union {
    struct {
        u32 tag : PXI_FIFOMESSAGE_BITSZ_TAG;
        u32 err : PXI_FIFOMESSAGE_BITSZ_ERR;
        u32 data : PXI_FIFOMESSAGE_BITSZ_DATA;
    } e;
    u32 raw;
} PXIFifoMessage;

#define PXI_PROC_ARM7 1

#endif
