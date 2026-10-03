#include "nitro/types.h"

typedef struct RecordPool RecordPool;

typedef struct Tween {
    u8 unknown_00[0x18];
    u32 unknownFlags : 2;
    u32 finished : 1;
    u8 unknown_1c[0x0c];
} Tween;

typedef struct SequenceWork {
    u8 unknown_00[0x04];
    int pageArgs[3];
    s16 step;
    u8 unknown_12[0x06];
    BOOL started;
    u8 unknown_1c[0x18];
    RecordPool *pool;
    u8 pages[3][0x28];
    u8 unknown_b0[0x1980];
    Tween tween;
} SequenceWork;

extern SequenceWork *data_ov045_020c0880;
extern u16 data_02060500;

extern void InvokeCallbackForRecordId_020bf0c4(RecordPool *pool, u32 recordId);
extern void StartUnitTween_020bf1f8(Tween *tween, int duration);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *value);
extern void func_ov045_020bf19c(RecordPool *pool, void *page, int arg, int flags);
extern BOOL func_ov045_020bf3bc(Tween *tween);
extern void func_ov045_020bf248(RecordPool *pool, int id);
extern void func_ov045_020bf26c(RecordPool *pool, int id);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void *func_ov001_0207123c(void);
extern void ClearTileTableRowAndMarkDirty_020b9d18(void *table, int row);
extern void func_ov027_020b7dd4(RecordPool *pool);

int RunIntroSequenceStep_020bfea0(void)
{
    SequenceWork *work = data_ov045_020c0880;

    if (work->step < 0) {
        return 0;
    }
    switch (work->step) {
    case 0:
        if (!work->started) {
            InvokeCallbackForRecordId_020bf0c4(work->pool, 0x230);
            StartUnitTween_020bf1f8(&work->tween, 800);
            work->started = TRUE;
        }
        SampleTweenValue_0205258c(&work->tween, NULL);
        if (work->tween.finished) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 1:
        if (!work->started) {
            InvokeCallbackForRecordId_020bf0c4(work->pool, 0x231);
            func_ov045_020bf19c(work->pool, work->pages[0], work->pageArgs[0], 0);
            StartUnitTween_020bf1f8(&work->tween, 800);
            work->started = TRUE;
        }
        if (func_ov045_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 2:
        if (!work->started) {
            InvokeCallbackForRecordId_020bf0c4(work->pool, 0x232);
            func_ov045_020bf19c(work->pool, work->pages[1], work->pageArgs[1], 0);
            StartUnitTween_020bf1f8(&work->tween, 800);
            work->started = TRUE;
        }
        if (func_ov045_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 3:
        if (!work->started) {
            InvokeCallbackForRecordId_020bf0c4(work->pool, 0x233);
            func_ov045_020bf19c(work->pool, work->pages[2], work->pageArgs[2], 0);
            StartUnitTween_020bf1f8(&work->tween, 800);
            work->started = TRUE;
        }
        if (func_ov045_020bf3bc(&work->tween)) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 4:
        if (!work->started) {
            func_ov045_020bf248(work->pool, 9);
            work->started = TRUE;
            break;
        }
        if (!(data_02060500 & 0x2f0f)) {
            break;
        }
        PlaySoundEffect_0204d924(0, 1);
        work->started = FALSE;
        work->step = -1;
        func_ov045_020bf26c(work->pool, 9);
    default:
        if (!work->started) {
            ClearTileTableRowAndMarkDirty_020b9d18(func_ov001_0207123c(), 0xb);
            ClearTileTableRowAndMarkDirty_020b9d18(func_ov001_0207123c(), 0xa);
            work->started = TRUE;
        }
        break;
    }
    func_ov027_020b7dd4(work->pool);
    return 0;
}
