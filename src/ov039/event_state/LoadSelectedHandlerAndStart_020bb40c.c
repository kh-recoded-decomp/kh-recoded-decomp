#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xc998];
    int handlerEvent;
    void *handlerWork;
    u8 pad_c9a0[0x20];
    int handlerParam;
    u8 pad_c9c4[0x6c];
    int handlerReady;
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern void func_ov039_020bcf20(int event);
extern void func_ov039_020bcf50(int param);
extern u32 func_ov039_020bd674(void);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int dispatchSelectedMenuCallback_020bcfcc(int event);
extern void func_ov039_020baae0(int value);
extern void InitStreamBufferPair_020bacbc(int blockCount, u32 flag);

void LoadSelectedHandlerAndStart_020bb40c(void)
{
    Ov039State *state = data_ov039_020bea00;

    func_ov039_020bcf20(state->handlerEvent);
    if (state->handlerWork == NULL) {
        u32 size;
        func_ov039_020bcf50(state->handlerParam);
        size = func_ov039_020bd674();
        state->handlerWork = NNSi_FndAllocFromDefaultHeap_0202a178(size);
        func_01ff8830(state->handlerWork, 0, size);
    }
    if (state->handlerReady == 0) {
        state->handlerReady = dispatchSelectedMenuCallback_020bcfcc((int)state->handlerWork);
    }
    if (state->handlerReady == 0) {
        return;
    }
    func_ov039_020baae0(6);
    InitStreamBufferPair_020bacbc(0, 100);
}
