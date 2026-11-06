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

extern FieldSceneHandle gFieldSceneGlobals;
extern SessionWork *gFieldSessionWork;
extern char data_ov045_020c0820[];
extern char OVERLAY_45_ID[];
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlay_id);
extern void *CreateTaskObject(void *descriptor, void *userData);
extern u32 GetSessionCounter(s32 index);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern int CountAreaEntriesOfKind0(void);
extern void SetupFieldBgLayers(void);
extern void SetFieldVisiblePlanes(void);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(void *dest, u32 srcOffset, u32 size);

void ReopenFieldScoreScreen(void)
{
    FieldScene *scene = gFieldSceneGlobals.scene;
    u32 saved = ReadSessionPackedBits(0x35a7, 0x20);
    ScoreScreenParams params;

    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_45_ID);
    params.flags = 2;
    params.bonus = GetSessionCounter(0);
    params.timeScore = CountAreaEntriesOfKind0() * 1000;
    params.total = params.timeScore + (saved + params.bonus);
    WriteSessionPackedBits(0x35a7, 0x20, params.total);
    gFieldSessionWork->pendingScore = 0;
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
        scene->resultScreen = CreateTaskObject(data_ov045_020c0820, &params);
    }
}
