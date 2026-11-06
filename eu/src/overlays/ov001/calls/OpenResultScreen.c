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

extern FieldSceneHandle gFieldSceneGlobals;
extern char gBattleGaugeTaskDescriptor[];
extern char OVERLAY_45_ID[];
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlay_id);
extern void *CreateTaskObject(void *descriptor, void *userData);
extern u32 GetSessionCounter(s32 index);
extern s32 func_ov001_020644c0(void);
extern int ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern u32 GetPostIntroElapsedMilliseconds(void);
extern int CountAreaEntriesOfKind0(void);

void OpenResultScreen(int rank, int arg)
{
    FieldScene *scene = gFieldSceneGlobals.scene;
    ResultScreenParams params;

    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_45_ID);
    params.flags = 0;
    params.mode = rank - 1;
    params.score = GetSessionCounter(0);
    params.extra = GetPostIntroElapsedMilliseconds();
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
        params.score = ReadSessionPackedBits(0x35a7, 0x20) + GetSessionCounter(0) + CountAreaEntriesOfKind0() * 1000;
    }
    scene->sceneFlags = (scene->sceneFlags & ~1) | 0x40;
    scene->resultScreen = CreateTaskObject(gBattleGaugeTaskDescriptor, &params);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
}
