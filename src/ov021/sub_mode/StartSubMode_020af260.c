#include "nitro/types.h"

typedef void *(*SubModeUpdateFunc)(void);

typedef struct SubModeState {
    s32 mode;
    void *block;
    SubModeUpdateFunc update;
    void **heap;
} SubModeState;

extern SubModeState *data_ov021_020b56a0;
extern s32 data_ov021_020b5290[];

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff86fc(u32 value, void *dest, u32 size);
extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void *NNSi_FndAllocFromExpHeapEx_0202a1e4(u32 size, void **heap);
extern void func_02029f78(int processor, int overlayId);
extern SubModeUpdateFunc func_ov046_020c08a0(void *arg, void *block);
extern SubModeUpdateFunc func_ov042_020bdb4c(void *arg, void *block);
extern SubModeUpdateFunc func_ov043_020bcbcc(void *arg, void *block);
extern SubModeUpdateFunc func_ov044_020d05e8(void *arg, void *block);

void StartSubMode_020af260(void *arg, void **heap, s32 mode)
{
    SubModeState initial;
    u32 blockSize;

    switch (mode) {
    case 0:
        blockSize = 0x414;
        break;
    case 1:
        blockSize = 0x5A8;
        break;
    case 2:
        blockSize = 0x138;
        break;
    case 3:
        blockSize = 0x194;
        break;
    default:
        blockSize = 0;
        break;
    }
    data_ov021_020b56a0 = (SubModeState *)NNSi_FndGetCurrentRootHeap_0202a764();
    func_01ff86fc(0, &initial, sizeof(initial));
    *data_ov021_020b56a0 = initial;
    data_ov021_020b56a0->heap = heap;
    data_ov021_020b56a0->mode = mode;
    if (blockSize != 0) {
        data_ov021_020b56a0->block = NNSi_FndAllocFromExpHeapEx_0202a1e4(blockSize, data_ov021_020b56a0->heap);
        func_01ff8830(data_ov021_020b56a0->block, 0, blockSize);
    } else {
        data_ov021_020b56a0->block = NULL;
    }
    func_02029f78(0, data_ov021_020b5290[mode]);
    switch (mode) {
    case 0:
        data_ov021_020b56a0->update = func_ov046_020c08a0(arg, data_ov021_020b56a0->block);
        break;
    case 1:
        data_ov021_020b56a0->update = func_ov042_020bdb4c(arg, data_ov021_020b56a0->block);
        break;
    case 2:
        data_ov021_020b56a0->update = func_ov043_020bcbcc(arg, data_ov021_020b56a0->block);
        break;
    case 3:
        data_ov021_020b56a0->update = func_ov044_020d05e8(arg, data_ov021_020b56a0->block);
        break;
    }
}
