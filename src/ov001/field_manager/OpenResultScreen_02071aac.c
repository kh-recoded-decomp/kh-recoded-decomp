#include "nitro/types.h"

typedef struct ResultScreenParams {
    u16 flags;
    u16 mode;
    int arg;
    u32 score;
    u32 extra;
} ResultScreenParams;

typedef struct FieldScene {
    u8 pad_000[0x42c];
    void *resultScreen;
    u8 pad_430[0x480 - 0x430];
    u32 sceneFlags;
} FieldScene;

typedef struct FieldSceneHandle {
    u32 unk_00;
    FieldScene *scene;
} FieldSceneHandle;

extern FieldSceneHandle data_ov001_020a04a4;
extern char data_ov045_020c0800[];
extern char OverlayId45_0000002d[];
extern void func_02029f78(int processor, int overlay_id);
extern void *func_0202a448(void *descriptor, void *userData);
extern u32 func_ov001_02063b68(s32 index);
extern s32 func_ov001_020644c0(void);
extern int ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern u32 func_ov001_02068e98(void);
extern int func_ov035_020bb2a0(void);

void OpenResultScreen_02071aac(int rank, int arg)
{
    FieldScene *scene = data_ov001_020a04a4.scene;
    ResultScreenParams params;

    func_02029f78(0, (int)OverlayId45_0000002d);
    params.flags = 0;
    params.mode = rank - 1;
    params.score = func_ov001_02063b68(0);
    params.extra = func_ov001_02068e98();
    params.arg = arg;
    if (scene->resultScreen != NULL) {
        return;
    }
    if (params.mode > 3) {
        params.mode += 2;
    } else if (params.mode == 3) {
        switch (func_ov001_020644c0()) {
        case 5:
            params.mode = 3;
            break;
        case 15:
            params.mode = 4;
            break;
        case 30:
            params.mode = 5;
            break;
        }
        params.score = ReadSessionPackedBits_02064574(0x35a7, 0x20) + func_ov001_02063b68(0) + func_ov035_020bb2a0() * 1000;
    }
    scene->sceneFlags = (scene->sceneFlags & ~1) | 0x40;
    scene->resultScreen = func_0202a448(data_ov045_020c0800, &params);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
}
