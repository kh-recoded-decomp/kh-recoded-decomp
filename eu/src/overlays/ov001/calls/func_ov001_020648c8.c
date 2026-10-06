#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xda];
    s16 sceneId;
    s16 subSceneId;
} SceneInfo;

typedef struct {
    u32 mode : 2;
    u32 finished : 1;
    u32 unk_3 : 8;
    u32 skipPreset : 1;
    u32 unk_12 : 20;
} SessionFlags;

typedef struct {
    u8 pad_0000[0x214];
    SessionFlags flags;
    u32 pendingValue;
    u8 pad_021c[0x2818 - 0x21c];
    void (*callback)(int arg);
    u8 pad_281c[0x28a4 - 0x281c];
    s8 callbackArg;
    u8 pad_28a5[0x29b8 - 0x28a5];
    SceneInfo *sceneInfo;
} Session;

extern Session *data_ov001_020a0480;
extern void LoadDifficultyPresetIntoSession(void);
extern void ConfigureFieldTracks(int sceneId, int subSceneId, int mode, int param);
extern void SetPendingFieldValue(int request);

void func_ov001_020648c8(u32 value)
{
    Session *session = data_ov001_020a0480;

    if (!session->flags.skipPreset)
    {
        LoadDifficultyPresetIntoSession();
        ConfigureFieldTracks(session->sceneInfo->sceneId, session->sceneInfo->subSceneId, 1, -1);
    }
    if (data_ov001_020a0480->callback != NULL)
    {
        data_ov001_020a0480->callback(data_ov001_020a0480->callbackArg);
    }
    data_ov001_020a0480->flags.finished = TRUE;
    data_ov001_020a0480->pendingValue = value;
    if (data_ov001_020a0480->flags.skipPreset)
    {
        SetPendingFieldValue(2);
    }
}
