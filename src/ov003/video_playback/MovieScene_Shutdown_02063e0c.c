#include "nitro/types.h"

#define REG_POWCNT1 (*(vu16 *)0x04000304)

typedef struct MovieScene {
    u8 pad_000[4];
    u8 sound[0x820];
    u8 resources[0xc];
    u8 pxi[0xa4];
    void *buffer;
} MovieScene;

extern MovieScene *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void PXI_Init_02064974(void *arg);
extern void FreeResourceBufferAndProbeHeap_02001474(void *resources);
extern void StoreGlobalArrayEntry_02025668(int index, int value);
extern void func_020257e4(void *sound);
extern void func_02029f98(int processor, int overlay_id);
extern void CreateManagerObjects_02028bcc(void);
extern char OverlayId22_00000016[];
extern MovieScene *data_ov003_020658c0;
extern s32 data_ov003_020650c0;

void MovieScene_Shutdown_02063e0c(void)
{
    MovieScene *scene = NNSi_FndGetCurrentRootHeap_0202a764();

    NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->buffer);
    PXI_Init_02064974(scene->pxi);
    FreeResourceBufferAndProbeHeap_02001474(scene->resources);
    StoreGlobalArrayEntry_02025668(3, 0);
    func_020257e4(scene->sound);
    func_02029f98(0, (int)OverlayId22_00000016);
    data_ov003_020658c0 = NULL;
    data_ov003_020650c0 = -1;
    REG_POWCNT1 |= 0x8000;
    CreateManagerObjects_02028bcc();
}
