#include "nitro/types.h"

typedef struct PaletteHeader {
    u8 unknown_00[0x14];
    const void *data;
} PaletteHeader;

typedef struct GaugeWork {
    void *source;
    void *buffer;
    void *cells;
    void *frameFile;
    PaletteHeader *frameHeader;
    u8 unknown_14[4];
    int level;
    u8 unknown_1c[0x114];
    int target;
    int current;
} GaugeWork;

typedef struct GaugeGlobals {
    void *unknown_00;
    GaugeWork *work;
} GaugeGlobals;

extern GaugeGlobals data_ov035_020bc4e8;
extern void *GetSceneTagTracker_020711b0(void);
extern GaugeWork *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern u32 MakePrimaryVramKey_020711ec(u32 slot);
extern void *func_0202c48c(u32 fileId, u32 alignFlag);
extern int func_02014d38(void *file, PaletteHeader **header);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff878c(const void *src, void *dest, u32 size);
extern void func_01ff8740(int value, void *dest, u32 size);
extern void func_ov035_020bbf70(GaugeWork *work);
extern void *FindLoadedElementById_020b8390(void *pool, int id);
extern void SetTagRecordArmed_020b83e8(void *pool, void *record, int armed);
extern void *FindActiveRecordById_020b8184(void *pool, int id);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov035_020bc0ec(void);

void *InitBarGauge_020bc00c(void) {
    PaletteHeader *header;
    void *pool = GetSceneTagTracker_020711b0();
    GaugeWork *work = NNSi_FndGetCurrentRootHeap_0202a764();
    void *file;

    data_ov035_020bc4e8.work = work;
    work->level = 0;
    work->current = 0;
    work->target = 0;
    file = func_0202c48c(MakePrimaryVramKey_020711ec(7), 0xe);
    func_02014d38(file, &header);
    work->source = NNSi_FndAllocFromDefaultHeap_0202a178(0x160);
    work->buffer = NNSi_FndAllocFromDefaultHeap_0202a178(0x160);
    func_01ff878c(header->data, work->source, 0x160);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    work->frameFile = func_0202c48c(MakePrimaryVramKey_020711ec(0xe), 0xe);
    func_02014d38(work->frameFile, &work->frameHeader);
    work->cells = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0xc0, -4);
    func_01ff8740(0, work->cells, 0xc0);
    func_ov035_020bbf70(work);
    SetTagRecordArmed_020b83e8(pool, FindLoadedElementById_020b8390(pool, 1), 0);
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 5));
    return func_ov035_020bc0ec;
}
