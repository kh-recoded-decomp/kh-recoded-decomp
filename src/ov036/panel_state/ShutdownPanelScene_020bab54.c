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

extern SlotSceneHolder data_ov036_020c3920;
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern int NNS_SndPlayerCountPlayingSeqByPlayerNo_0201d6c0(int playerNo);
extern void func_0204d980(void);
extern int func_02029f48(void);
extern void ClearScreenLayerGraphics_020bbb64(ScreenLayer *layer, int screen);
extern BOOL ReleaseResourceSlot_0202ca18(void *slot);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);
extern int FreeBufferAndClearStatus_0206a918(SlotEntry *slot);
extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void ResetSlotScene_020bb428(void);
extern void ReleaseSeqArcHeapLevel_0204e040(int index);

int ShutdownPanelScene_020bab54(void)
{
    int i;
    SlotScene *scene = data_ov036_020c3920.scene;

    SetBrightnessAndSyncMain_02029e7c(scene->brightness);
    SetSecondaryBrightness_02029ed0(-16);
    for (i = 2; i < 32; i++) {
        if (NNS_SndPlayerCountPlayingSeqByPlayerNo_0201d6c0(i) > 0) {
            scene->soundWaitFrames++;
            if (scene->soundWaitFrames > 60) {
                func_0204d980();
            } else {
                return -1;
            }
        }
    }
    scene->soundWaitFrames = 0;
    if (func_02029f48() != 0) {
        for (i = 0; i < 2; i++) {
            ClearScreenLayerGraphics_020bbb64(&scene->layers[i], i);
        }
        for (i = 0; i < 8; i++) {
            if (scene->slots[i].record != NULL) {
                ReleaseResourceSlot_0202ca18(scene->slots[i].record);
                ReleaseSharedRecordSlot_0202c8a8(scene->slots[i].record);
            }
            FreeBufferAndClearStatus_0206a918(&scene->slots[i]);
        }
        for (i = 0; i < 5; i++) {
            if (scene->actors[i].active != 0) {
                ReleaseResourceAndDetach_0202eee8(scene->actors[i].node);
            }
        }
        ResetSlotScene_020bb428();
    }
    scene->pendingScript = 0;
    scene->deferred = 0;
    scene->flags &= ~0x10;
    ReleaseSeqArcHeapLevel_0204e040(1);
    data_ov036_020c3920.scene->flags |= 0x8000;
    return 2;
}
