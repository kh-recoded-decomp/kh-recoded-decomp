#include "nitro/types.h"

typedef struct GaugeWork {
    u8 unknown_000[0x18];
    int level;
    u8 unknown_01c[0x114];
    int fill;
} GaugeWork;

typedef struct GaugeGlobals {
    void *unknown_00;
    GaugeWork *work;
} GaugeGlobals;

extern GaugeGlobals data_ov035_020bc4e8;
extern void *GetSceneTagTracker_020711b0(void);
extern void *FindLoadedElementById_020b8390(void *pool, int id);
extern void SetTagRecordArmed_020b83e8(void *pool, void *record, int armed);
extern void *FindActiveRecordById_020b8184(void *pool, int id);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void QueueColorUpload_020bb7d8(BOOL high);

void SetGaugeLevel_020bbef0(int level) {
    GaugeWork *work = data_ov035_020bc4e8.work;
    void *pool = GetSceneTagTracker_020711b0();

    if (work == NULL) {
        return;
    }
    if (level == 100) {
        SetTagRecordArmed_020b83e8(pool, FindLoadedElementById_020b8390(pool, 1), 1);
    } else if (work->level == 100) {
        SetTagRecordArmed_020b83e8(pool, FindLoadedElementById_020b8390(pool, 1), 0);
        TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 5));
    }
    if (level > 0) {
        work->fill = (level * 87) / 100;
    } else {
        work->fill = 0;
    }
    QueueColorUpload_020bb7d8(level >= 40);
    work->level = level;
}
