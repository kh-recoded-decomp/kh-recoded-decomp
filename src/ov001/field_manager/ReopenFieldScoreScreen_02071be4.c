#include "nitro/types.h"

typedef struct ScoreScreenParams {
    u16 flags;
    u16 mode;
    u32 bonus;
    int timeScore;
    u32 total;
} ScoreScreenParams;

typedef struct FieldScene {
    u8 pad_000[0x42c];
    void *resultScreen;
    u8 pad_430[0x448 - 0x430];
    void *bg3Char;
    void *bg2Char;
    u8 pad_450[0x45c - 0x450];
    void *objChar;
    u8 pad_460[0x480 - 0x460];
    u32 sceneFlags;
} FieldScene;

typedef struct FieldSceneHandle {
    u32 unk_00;
    FieldScene *scene;
} FieldSceneHandle;

typedef struct SessionWork {
    u8 pad_0000[0x2938];
    s32 pendingScore;
} SessionWork;

extern FieldSceneHandle data_ov001_020a04a4;
extern SessionWork *data_ov001_020a0460;
extern char data_ov045_020c0800[];
extern char OverlayId45_0000002d[];
extern void func_02029f78(int processor, int overlay_id);
extern void *func_0202a448(void *descriptor, void *userData);
extern u32 func_ov001_02063b68(s32 index);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern int func_ov035_020bb2a0(void);
extern void SetupFieldBgLayers_0206ec80(void);
extern void SetFieldVisiblePlanes_0206ec3c(void);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void func_02007250(void *dest, u32 srcOffset, u32 size);

void ReopenFieldScoreScreen_02071be4(void)
{
    FieldScene *scene = data_ov001_020a04a4.scene;
    u32 saved = ReadSessionPackedBits_02064574(0x35a7, 0x20);
    ScoreScreenParams params;

    func_02029f78(0, (int)OverlayId45_0000002d);
    params.flags = 2;
    params.bonus = func_ov001_02063b68(0);
    params.timeScore = func_ov035_020bb2a0() * 1000;
    params.total = params.timeScore + (saved + params.bonus);
    WriteSessionPackedBits_0206459c(0x35a7, 0x20, params.total);
    data_ov001_020a0460->pendingScore = 0;
    if (scene->resultScreen == NULL) {
        scene->sceneFlags &= ~1;
        scene->sceneFlags &= ~0x40;
        SetupFieldBgLayers_0206ec80();
        SetFieldVisiblePlanes_0206ec3c();
        if (scene->bg3Char != NULL) {
            GX_LoadBG3Char_02007b70(scene->bg3Char, 0, 0x5800);
            GX_LoadBG2Char_02007a90(scene->bg2Char, 0, 0x1000);
        }
        if (scene->objChar != NULL) {
            func_02007250(scene->objChar, 0, 0x200);
        }
        scene->resultScreen = func_0202a448(data_ov045_020c0800, &params);
    }
}
