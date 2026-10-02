#include "nitro/types.h"

typedef struct WindowSound {
    u8 pad_00[0x10];
    int enabled;
} WindowSound;

typedef struct ModeWindow {
    int layer;
    int unk4;
    int state;
    u8 pad_0c[0x10];
    u8 fade[0x38];
    WindowSound sound;
} ModeWindow;

extern int *data_ov001_020a04c4;
extern int func_ov001_0207123c(void);
extern void *GetSceneTagTracker_020711b0(void);
extern void *func_ov027_020b8390(void *pool, int tag);
extern void func_ov027_020b83e8(void *pool, void *record, int value);
extern void func_02052514(void *record, int value0, int value1, int value2, int value3);
extern void func_0205255c(void *record);
extern void RefreshWindowHighlight_02079490(ModeWindow *window, int unused, int layer);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void FreeModeResources_0207942c(ModeWindow *window);
extern void func_ov001_020795c4(ModeWindow *window);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *arg);

void CloseModeWindow_0207a260(ModeWindow *window) {
    void *pool;
    WindowSound *sound;
    void *record;

    func_ov001_0207123c();
    pool = GetSceneTagTracker_020711b0();
    sound = &window->sound;
    func_ov027_020b83e8(pool, func_ov027_020b8390(pool, 6), 0);
    func_ov027_020b83e8(pool, func_ov027_020b8390(pool, 13), 0);
    func_ov027_020b83e8(pool, func_ov027_020b8390(pool, 14), 0);
    func_02052514(window->fade, 0, 0x64000, 0, 100);
    func_0205255c(window->fade);
    RefreshWindowHighlight_02079490(window, window->layer, 9);
    RefreshWindowHighlight_02079490(window, window->layer, 10);
    if (*data_ov001_020a04c4 == 1) {
        if (window->sound.enabled != 0) {
            PlaySoundEffect_0204d924(0, 1);
        }
        FreeModeResources_0207942c(window);
        window->state = 0;
        RefreshWindowHighlight_02079490(window, window->layer, 11);
        return;
    }
    func_ov001_020795c4(window);
    window->state = 7;
    switch (*data_ov001_020a04c4) {
    default:
        goto play;
    case 5:
    case 7:
    case 10:
        record = FindActiveRecordById_020b8184(pool, 600);
        break;
    case 6:
        record = FindActiveRecordById_020b8184(pool, 601);
        break;
    }
    InvokeCallback40_020b8268(pool, record);
play:
    if (sound->enabled != 0) {
        PlaySoundEffect_0204d924(0, 1);
        return;
    }
    PlaySoundEffect_0204d924(0, 7);
}
