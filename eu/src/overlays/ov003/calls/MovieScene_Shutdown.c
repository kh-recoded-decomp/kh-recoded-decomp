#include "nitro/types.h"

#define REG_POWCNT1 (*(vu16 *)0x04000304)

typedef struct MovieScene {
    u8 pad_000[4];
    u8 sound[0x820];
    u8 resources[0xc];
    u8 pxi[0xa4];
    void *buffer;
} MovieScene;

extern MovieScene *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void func_ov003_02064974(void *arg);
extern void FreeResourceBufferAndProbeHeap(void *resources);
extern void StoreGlobalArrayEntry(int index, int value);
extern void func_020257f8(void *sound);
extern void func_02029fac(int processor, int overlay_id);
extern void CreateManagerObjects(void);
extern char OVERLAY_22_ID[];
extern MovieScene *data_ov003_020658c0;
extern s32 data_ov003_020650c0;

void MovieScene_Shutdown(void)
{
    MovieScene *scene = NNSi_FndGetCurrentRootHeap();

    NNSi_FndFreeFromDefaultHeap(scene->buffer);
    func_ov003_02064974(scene->pxi);
    FreeResourceBufferAndProbeHeap(scene->resources);
    StoreGlobalArrayEntry(3, 0);
    func_020257f8(scene->sound);
    func_02029fac(0, (int)OVERLAY_22_ID);
    data_ov003_020658c0 = NULL;
    data_ov003_020650c0 = -1;
    REG_POWCNT1 |= 0x8000;
    CreateManagerObjects();
}
