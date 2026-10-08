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

extern FieldSceneHandle data_ov001_020a04c4;
extern SessionWork *data_ov001_020a0480;
extern char data_ov045_020c0820[];
extern char OVERLAY_45_ID[];
extern void func_02029f8c(int processor, int overlay_id);
extern void *func_0202a45c(void *descriptor, void *userData);
extern u32 func_ov001_02063b68(s32 index);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern int func_ov035_020bb2c0(void);
extern void SetupFieldBgLayers(void);
extern void SetFieldVisiblePlanes(void);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(void *dest, u32 srcOffset, u32 size);

void ReopenFieldScoreScreen(void)
{
    FieldScene *scene = data_ov001_020a04c4.scene;
    u32 saved = ReadSessionPackedBits(0x35a7, 0x20);
    ScoreScreenParams params;

    func_02029f8c(0, (int)OVERLAY_45_ID);
    params.flags = 2;
    params.bonus = func_ov001_02063b68(0);
    params.timeScore = func_ov035_020bb2c0() * 1000;
    params.total = params.timeScore + (saved + params.bonus);
    WriteSessionPackedBits(0x35a7, 0x20, params.total);
    data_ov001_020a0480->pendingScore = 0;
    if (scene->resultScreen == NULL) {
        scene->sceneFlags &= ~1;
        scene->sceneFlags &= ~0x40;
        SetupFieldBgLayers();
        SetFieldVisiblePlanes();
        if (scene->bg3Char != NULL) {
            GX_LoadBG3Char(scene->bg3Char, 0, 0x5800);
            GX_LoadBG2Char(scene->bg2Char, 0, 0x1000);
        }
        if (scene->objChar != NULL) {
            GX_LoadBGPltt(scene->objChar, 0, 0x200);
        }
        scene->resultScreen = func_0202a45c(data_ov045_020c0820, &params);
    }
}
