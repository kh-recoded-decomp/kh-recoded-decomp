/* Memory interface: copies, fills, DMA, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_MI_H
#define NITRO_MI_H

#include "nitro/types.h"
#include "nitro/hw.h"

struct MIAllocator;

typedef void (*MIDmaCallback)(void *);

#define MI_CpuFillFast(dest, data, size) MIi_CpuClearFast((data), (dest), (size))

typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);

typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);

typedef void * (*MIAllocatorAllocFunction)(void * userdata, u32 length, u32 alignment);

typedef void (*MIAllocatorFreeFunction)(void * userdata, void * buffer);

typedef struct MIAllocator {
    void * userdata;
    MIAllocatorAllocFunction Alloc;
    MIAllocatorFreeFunction Free;
} MIAllocator;

typedef enum { MI_CTRDG_ROMCYCLE1_10 = 0, MI_CTRDG_ROMCYCLE1_8, MI_CTRDG_ROMCYCLE1_6, MI_CTRDG_ROMCYCLE1_18 } MICartridgeRomCycle1st;

typedef enum { MI_CTRDG_ROMCYCLE2_6 = 0, MI_CTRDG_ROMCYCLE2_4 } MICartridgeRomCycle2nd;

typedef enum { MI_PROCESSOR_ARM9 = 0, MI_PROCESSOR_ARM7 } MIProcessor;

#define MI_CpuCopy32 MIi_CpuCopy32

#define MI_CpuClear8(dst, size) MI_CpuFill8((dst), 0, (size))

#define MI_CpuFill32(dest, data, size) INITi_CpuClear32_0x01ff86fc((data), (dest), (size))

typedef struct {
    u8 * destp;
    s32 destCount;
    u32 length;
    u16 destTmp;
    u8 destTmpCnt;
    u8 flags;
    u8 flagIndex;
    u8 lengthFlg;
    u8 exFormat;
    u8 _padding[1];
} MIUncompContextLZ;

typedef struct {
    u32 compParam :4;
    u32 compType :4;
    u32 destSize :24;
} MICompressionHeader;

#define MI_DMA_ENABLE               (1UL << 31)

#define MI_DMA_IF_ENABLE            (1UL << 30)

#define MI_DMA_TIMING_IMM           (0UL << 27)

#define MI_DMA_TIMING_CARD          (5UL << 27)

#define MI_DMA_TIMING_GXFIFO        (7UL << 27)

#define MIi_DMA_TIMING_ANY          (u32)(~0)

#define MI_DMA_16BIT_BUS            (0UL << 26)

#define MI_DMA_32BIT_BUS            (1UL << 26)

#define MI_DMA_CONTINUOUS_ON        (1UL << 25)

#define MI_DMA_SRC_INC              (0UL << 23)

#define MI_DMA_SRC_DEC              (1UL << 23)

#define MI_DMA_SRC_FIX              (2UL << 23)

#define MI_DMA_DEST_INC             (0UL << 21)

#define MI_DMA_DEST_FIX             (2UL << 21)

#define MI_DMA_IMM16ENABLE          (MI_DMA_ENABLE | MI_DMA_TIMING_IMM | MI_DMA_16BIT_BUS)

#define MI_DMA_IMM32ENABLE          (MI_DMA_ENABLE | MI_DMA_TIMING_IMM | MI_DMA_32BIT_BUS)

#define MI_CNT_COPY16(size)         (MI_DMA_IMM16ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_INC | ((size) / 2))

#define MI_CNT_COPY32(size)         (MI_DMA_IMM32ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_INC | ((size) / 4))

#define MI_CNT_COPY32_IF(size)      (MI_CNT_COPY32((size)) | MI_DMA_IF_ENABLE)

#define MI_CNT_SEND32(size)         (MI_DMA_IMM32ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | ((size) / 4))

#define MI_CNT_SEND32_IF(size)      (MI_CNT_SEND32((size)) | MI_DMA_IF_ENABLE)

#define MI_CNT_CARDRECV32(size)     (MI_DMA_ENABLE | MI_DMA_TIMING_CARD | MI_DMA_SRC_FIX | MI_DMA_DEST_INC | MI_DMA_32BIT_BUS | ((size) / 4))

#define MI_CNT_GXCOPY(size)         (MI_DMA_ENABLE | MI_DMA_TIMING_GXFIFO | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | MI_DMA_32BIT_BUS | ((size) / 4))

#define MI_CNT_GXCOPY_IF(size)      (MI_CNT_GXCOPY(size) | MI_DMA_IF_ENABLE)

#define MIi_GX_LENGTH_ONCE          (118 * sizeof(u32))

#define MIi_Wait_BeforeDMA(dmaCntp, dmaNo) \
    do { \
        dmaCntp = &((vu32 *)REG_DMA0SAD_ADDR)[dmaNo * 3 + 2]; \
        while (*dmaCntp & REG_MI_DMA0CNT_E_MASK) {} \
    } while (0)

#define MIi_Wait_AfterDMA(dmaCntp) \
    do { \
        while (*dmaCntp & REG_MI_DMA0CNT_E_MASK) {} \
    } while (0)

typedef struct {
    volatile BOOL isBusy;         /* 0x00 */
    u32 dmaNo;                    /* 0x04 */
    u32 src;                      /* 0x08 */
    u32 length;                   /* 0x0c */
    MIDmaCallback callback;       /* 0x10 */
    void *arg;                    /* 0x14 */
    int fifoCond;                 /* 0x18: GXFifoIntrCond */
    void (*fifoFunc)(void);       /* 0x1c */
} MIiGXDmaParams;

#define MINOBJSIZE      (HEADERSIZE + ALIGNMENT)

#define MI_DMA_MAX_NUM          3

#define MI_CpuClear32(dst, size) INITi_CpuClear32_0x01ff86fc(0, (dst), (size))

#define MI_CpuClear16(dst, size) MIi_CpuClear16(0, (dst), (size))

#define MI_CpuCopy16(src, dst, size) MIi_CpuCopy16((src), (dst), (size))

#define MIN_ALIGNMENT 4

#endif
