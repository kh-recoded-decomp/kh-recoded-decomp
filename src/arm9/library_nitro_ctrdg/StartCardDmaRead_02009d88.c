#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 source;
    u32 destination;
} CardReadRequest;

typedef struct {
    u8 pad_00[8];
    CardReadRequest *request;
} CardReadState;

typedef struct {
    void (*copy)(u32 channel, u32 source, u32 destination, u32 length);
} CardDmaInterface;

typedef struct {
    u8 pad_00[8];
    u32 channel;
    CardDmaInterface *dma;
} CardDmaConfig;

extern CardReadState data_02057620;
extern CardDmaConfig data_020574e0;
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_02009d24(void);
extern void OS_SetIrqFunction_02001d90(u32 intrBits, void (*function)(void));
extern u32 OS_ResetRequestIrqMask_02001fbc(u32 mask);
extern u32 OS_EnableIrqMask_02001f5c(u32 mask);
extern void func_02009b0c(u32 source);

void StartCardDmaRead_02009d88(CardReadRequest *request) {
    u32 state = func_02004938();

    data_02057620.request = request;
    OS_SetIrqFunction_02001d90(0x80000, func_02009d24);
    OS_ResetRequestIrqMask_02001fbc(0x80000);
    OS_EnableIrqMask_02001f5c(0x80000);
    func_0200494c(state);

    data_020574e0.dma->copy(data_020574e0.channel, 0x4100010, request->destination, 0x200);
    func_02009b0c(request->source);
}
