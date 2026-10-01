#include "nitro/types.h"

typedef struct CardDmaInterface {
    void (*copy)(u32 channel, const void *src, void *dst, u32 length);
    void (*stop)(u32 channel);
} CardDmaInterface;

typedef struct CardRomRequest {
    u32 pad_00;
    void (*callback)(void);
    u32 offset;
    u32 source;
    void *destination;
    u32 length;
    u32 position;
} CardRomRequest;

typedef struct CardRomState {
    u32 base;
    BOOL flushCache;
    u32 pad_08;
    void (*readFunc)(void);
    CardRomRequest request;
} CardRomState;

typedef struct CardCommon {
    u8 pad_00[0xc];
    u32 cacheThresholdA;
    u32 cacheThresholdB;
    u8 pad_14[0x4fc - 0x14];
    u32 source;
    void *destination;
    u32 length;
    u32 dmaChannel;
    const CardDmaInterface *dma;
} CardCommon;

extern CardCommon data_02056fe0;
extern CardRomState data_02057620;
extern BOOL data_02055c20[];
extern void CARD_CheckEnabled_0200910c(void);
extern u32 SelectCodeByFlag_02009278(void);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern BOOL func_020093d0(CardCommon *common, int setArgs, u32 callback, u32 arg);
extern const CardDmaInterface *CARDi_GetDmaInterface_0200946c(u32 channel);
extern BOOL func_02009e00(u32 channel, void *destination, u32 source, u32 length);
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_02009498(void *destination, u32 length, u32 threshold);
extern void CARDi_DCInvalidateSmart_020094ac(void *destination, u32 length, u32 threshold);
extern void StartCardDmaRead_02009d88(CardRomRequest *request);
extern void PXI_Init_0200a044(void);
extern BOOL CARDi_ExecuteOldTypeTask_02009344(void (*task)(CardCommon *common), BOOL async);
extern void func_02009ddc(void);
extern void func_02009c4c(void);
extern void func_02009e80(CardCommon *common);

void CARDi_ReadRom_02009ebc(u32 dmaChannel, u32 source, void *destination, u32 length, u32 callback, u32 arg, BOOL async)
{
    CardCommon *common = &data_02056fe0;

    CARD_CheckEnabled_0200910c();
    if ((SelectCodeByFlag_02009278() & 4) == 0) {
        RunResetCallbackAndIdle_02004cf0();
    }
    func_020093d0(common, 1, callback, arg);
    common->dma = CARDi_GetDmaInterface_0200946c(dmaChannel);
    common->dmaChannel = common->dma != NULL ? (dmaChannel & 3) : (u32)-1;
    if (common->dmaChannel <= 3) {
        common->dma->stop(common->dmaChannel);
    }
    common->source = source + data_02057620.base;
    common->destination = destination;
    common->length = length;
    data_02057620.request.callback = func_02009ddc;
    data_02057620.request.offset = 0;
    data_02057620.request.source = common->source;
    data_02057620.request.destination = destination;
    data_02057620.request.length = length;
    data_02057620.request.position = 0;
    if (data_02057620.readFunc == func_02009c4c
        && func_02009e00(common->dmaChannel, destination, common->source, length)) {
        u32 state = func_02004938();

        if (data_02057620.flushCache) {
            func_02009498(common->destination, common->length, common->cacheThresholdA);
        }
        if (data_02055c20[1]) {
            CARDi_DCInvalidateSmart_020094ac(common->destination, common->length, common->cacheThresholdB);
        }
        func_0200494c(state);
        StartCardDmaRead_02009d88(&data_02057620.request);
        if (!async) {
            PXI_Init_0200a044();
        }
    } else {
        if (data_02057620.flushCache) {
            func_02009498(common->destination, common->length, common->cacheThresholdA);
        }
        CARDi_ExecuteOldTypeTask_02009344(func_02009e80, async);
    }
}
