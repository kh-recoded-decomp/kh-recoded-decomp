#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 data[0x54];
} ScreenLayer;

typedef struct SlotEntry {
    u8 pad_00[0x74];
    void *record;
    u8 pad_78[0x9c - 0x78];
} SlotEntry;

typedef struct ActorEntry {
    u8 pad_000[0x24];
    u8 node[0x98 - 0x24];
    int active;
    u8 pad_09c[0x138 - 0x9c];
} ActorEntry;

typedef struct SlotScene {
    u8 pad_0000[0x6];
    u16 flags;
    u8 pad_0008[0xc7c - 0x8];
    int pendingScript;
    int deferred;
    u8 pad_0c84[0xe88 - 0xc84];
    int brightness;
    u8 pad_0e8c[0x1090 - 0xe8c];
    SlotEntry *slots;
    ActorEntry *actors;
    ScreenLayer *layers;
    u8 pad_109c[0x10e8 - 0x109c];
    int soundWaitFrames;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern int NNS_SndPlayerCountPlayingSeqByPlayerNo(int playerNo);
extern void func_0204d994(void);
extern int func_02029f5c(void);
extern void ClearScreenLayerGraphics(ScreenLayer *layer, int screen);
extern BOOL ReleaseResourceSlot(void *slot);
extern int ReleaseSharedRecordSlot(void *slot);
extern int func_ov001_0206a918(SlotEntry *slot);
extern void ReleaseResourceAndDetach(u8 *object);
extern void ResetSlotScene(void);
extern void ReleaseSeqArcHeapLevel(int index);

int ShutdownPanelScene_020bab74(void)
{
    int i;
    SlotScene *scene = data_ov036_020c3940.scene;

    SetBrightnessAndSyncMain(scene->brightness);
    SetSecondaryBrightness(-16);
    for (i = 2; i < 32; i++) {
        if (NNS_SndPlayerCountPlayingSeqByPlayerNo(i) > 0) {
            scene->soundWaitFrames++;
            if (scene->soundWaitFrames > 60) {
                func_0204d994();
            } else {
                return -1;
            }
        }
    }
    scene->soundWaitFrames = 0;
    if (func_02029f5c() != 0) {
        for (i = 0; i < 2; i++) {
            ClearScreenLayerGraphics(&scene->layers[i], i);
        }
        for (i = 0; i < 8; i++) {
            if (scene->slots[i].record != NULL) {
                ReleaseResourceSlot(scene->slots[i].record);
                ReleaseSharedRecordSlot(scene->slots[i].record);
            }
            func_ov001_0206a918(&scene->slots[i]);
        }
        for (i = 0; i < 5; i++) {
            if (scene->actors[i].active != 0) {
                ReleaseResourceAndDetach(scene->actors[i].node);
            }
        }
        ResetSlotScene();
    }
    scene->pendingScript = 0;
    scene->deferred = 0;
    scene->flags &= ~0x10;
    ReleaseSeqArcHeapLevel(1);
    data_ov036_020c3940.scene->flags |= 0x8000;
    return 2;
}
