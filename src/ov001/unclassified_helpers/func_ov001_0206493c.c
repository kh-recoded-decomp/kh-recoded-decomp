#include "nitro/types.h"

typedef struct {
    u32 mode : 2;
    u32 finished : 1;
    u32 unk_3 : 2;
    u32 bit5 : 1;
    u32 unk_6 : 8;
    u32 bit14 : 1;
    u32 unk_15 : 17;
} SessionFlags;

typedef struct {
    u8 pad_0000[0x214];
    SessionFlags flags;
} Session;

extern Session *data_ov001_020a0460;
extern int func_02027348(int bitOffset, int bitCount);
extern void StoreSessionDifficultyPreset_0206452c(void);
extern void func_ov001_0206317c(int sceneId, int subSceneId, int mode, int param);

void func_ov001_0206493c(void)
{
    int sceneId;

    if (func_02027348(0x1a00, 2) != 0)
    {
        StoreSessionDifficultyPreset_0206452c();
    }
    sceneId = func_02027348(0x330b, 10);
    func_ov001_0206317c(sceneId, func_02027348(0x3315, 10), 1, 0);
    data_ov001_020a0460->flags.bit5 = TRUE;
    data_ov001_020a0460->flags.bit14 = TRUE;
}
