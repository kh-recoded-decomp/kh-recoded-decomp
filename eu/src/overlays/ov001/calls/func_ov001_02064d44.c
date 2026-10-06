#include "nitro/types.h"

typedef struct {
    u32 mode : 2;
    u32 unk_2 : 13;
    u32 bit15 : 1;
    u32 unk_16 : 16;
} SessionFlags;

typedef struct {
    s16 sceneId;
    s16 subSceneId;
    s16 nextSceneId;
    s16 nextSubSceneId;
    s16 request;
    u8 pad_0a[2];
    SessionFlags flags;
} SessionSceneState;

typedef struct {
    u8 pad_000[0x208];
    SessionSceneState scene;
} Session;

extern Session *data_ov001_020a0480;
extern void func_ov001_02068dfc(void);

void func_ov001_02064d44(void)
{
    SessionSceneState *scene = &data_ov001_020a0480->scene;

    if (scene->flags.bit15)
    {
        func_ov001_02068dfc();
        scene->flags.bit15 = FALSE;
    }
}
