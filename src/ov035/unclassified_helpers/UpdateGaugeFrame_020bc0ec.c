#include "nitro/types.h"

typedef struct LevelEntry {
    u8 header[0x0c];
    u16 levelA;
    u16 levelB;
    u16 scale;
    u8 unknown_12[2];
} LevelEntry;

typedef struct GaugeWork {
    void *source;
    void *buffer;
    void *cells;
    void *frameFile;
    void *frameHeader;
    BOOL dirty;
    int level;
    u8 unknown_1c[0x18];
    u16 channelValue[3];
    u8 unknown_3a[2];
    LevelEntry entries[12];
    int entryCount;
    int target;
    int current;
} GaugeWork;

typedef struct GaugeGlobals {
    void *unknown_00;
    GaugeWork *work;
} GaugeGlobals;

extern GaugeGlobals data_ov035_020bc4e8;
extern int data_0205fde4;
extern void func_ov035_020bae64(void);
extern int func_ov035_020bae1c(void);
extern int func_ov001_02067ed4(void);
extern void *PXI_Init_02028dac(void);
extern void *PXI_Init_02028db8(void);
extern void func_ov035_020bbef0(int level);
extern BOOL IsFieldPanelHidden_0207187c(void);
extern void func_ov035_020bbf70(GaugeWork *work);
extern void func_ov035_020bb96c(GaugeWork *work, int channel);
extern void func_ov035_020bbc4c(GaugeWork *work, LevelEntry *entry, u16 levelA, u16 levelB, u16 scale);
extern int GFXi_EnqueueCommand_02014090(void *a, int b, int c, int d);

int UpdateGaugeFrame_020bc0ec(void) {
    GaugeWork *work = data_ov035_020bc4e8.work;
    int level;
    int mode;
    int i;

    func_ov035_020bae64();
    level = func_ov035_020bae1c();
    mode = func_ov001_02067ed4();
    PXI_Init_02028dac();
    if (mode == 0x1f || mode == 0x20) {
        level = 0;
    } else if (level > 100) {
        level = 100;
    } else if (level < 0) {
        level = 0;
    }
    if (level != work->level) {
        func_ov035_020bbef0(level);
    }
    if (work->current != work->target && IsFieldPanelHidden_0207187c()) {
        func_ov035_020bbf70(work);
    }
    if (data_0205fde4 == 0) {
        for (i = 0; i < 3; i++) {
            if (work->channelValue[i] != 0) {
                func_ov035_020bb96c(work, i);
            }
        }
        for (i = 0; i < work->entryCount; i++) {
            func_ov035_020bbc4c(work, &work->entries[i], work->entries[i].levelA, work->entries[i].levelB, work->entries[i].scale);
        }
        work->entryCount = 0;
    }
    if (work->dirty) {
        GFXi_EnqueueCommand_02014090((void *)7, 0x5740, (int)work->cells, 0xc0);
        work->dirty = FALSE;
    }
    PXI_Init_02028db8();
    return 0;
}
