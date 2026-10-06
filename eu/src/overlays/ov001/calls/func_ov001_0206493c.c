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

extern Session *data_ov001_020a0480;
extern int ReadGlobalPackedBits(int bitOffset, int bitCount);
extern void StoreSessionDifficultyPreset(void);
extern void ConfigureFieldTracks(int sceneId, int subSceneId, int mode, int param);

void func_ov001_0206493c(void)
{
    int sceneId;

    if (ReadGlobalPackedBits(0x1a00, 2) != 0)
    {
        StoreSessionDifficultyPreset();
    }
    sceneId = ReadGlobalPackedBits(0x330b, 10);
    ConfigureFieldTracks(sceneId, ReadGlobalPackedBits(0x3315, 10), 1, 0);
    data_ov001_020a0480->flags.bit5 = TRUE;
    data_ov001_020a0480->flags.bit14 = TRUE;
}
