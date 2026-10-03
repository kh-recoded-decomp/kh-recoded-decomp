#include "nitro/types.h"

extern int data_ov039_020bea00;
extern int func_ov039_020bd624(void);
extern void func_ov039_020baae0(int phase);
extern void InitStreamBufferPair_020bacbc(int blockCount, u32 flag);
extern void SetMenuButtonsEnabled_020bae84(BOOL enable);

void StartSubScene_020bbf78(int sceneId, int fadeFrames, BOOL markPending)
{
    int active = func_ov039_020bd624();
    int base = data_ov039_020bea00;

    *(int *)(base + 0xc9bc) = sceneId;
    if (active == -1) {
        func_ov039_020baae0(1);
        *(int *)(base + 0xca0c) = 1;
        return;
    }
    if (fadeFrames < 0) {
        fadeFrames = 100;
    }
    *(u8 *)(base + 0xca44) = 1;
    func_ov039_020baae0(4);
    InitStreamBufferPair_020bacbc(-16, fadeFrames);
    SetMenuButtonsEnabled_020bae84(FALSE);
    if (markPending) {
        *(int *)(base + 0xca0c) = 1;
    }
    *(u16 *)(base + 0xca70) = 0;
    *(u16 *)(base + 0xca6e) = 0;
    *(u16 *)(base + 0xca6c) = 0;
}
