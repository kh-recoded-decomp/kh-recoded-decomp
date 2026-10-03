#include "nitro/types.h"

typedef struct SceneWork {
    u16 mode;
    u8 pad_02[0x1e];
    int gaugeEnabled;
    void *containerB;
    void *containerA;
    u8 pad_2c[0x0c];
    u8 elements[0x184c];
    u8 altObjects[0x138];
    u8 objects[0x48];
    void *container;
    u8 heapHolder[0x28];
} SceneWork;

extern SceneWork *data_ov045_020c0880;

extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void ReleaseRecordManager_02051cdc(void);
extern void SweepElements_020b831c(void *elements);
extern void func_ov027_020b7dfc(void *elements);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void ReleaseHeapBlockIfAllocated_020c0320(void *holder);
extern void ZeroHalfThenFree_0202cd78(void *container);
extern void G3X_SetClearColor_02006c08(unsigned color, unsigned alpha, unsigned depth, unsigned polygonId, BOOL fog);
extern void SetMenuGaugeActive_0207512c(int index, BOOL enable);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)

void ShutdownScene_020bef74(void)
{
    SceneWork *work = data_ov045_020c0880;

    if (work->mode == 0) {
        ReleaseRecordSlot_02051dfc(0);
        ReleaseRecordManager_02051cdc();
        SweepElements_020b831c(work->elements);
        func_ov027_020b7dfc(work->elements);
        DestroyFndObjectList_020014f0(work->objects);
        ReleaseHeapBlockIfAllocated_020c0320(work->heapHolder);
        ZeroHalfThenFree_0202cd78(work->container);
    } else if (work->mode == 3) {
        ReleaseRecordSlot_02051dfc(0);
        ReleaseRecordManager_02051cdc();
        SweepElements_020b831c(work->elements);
        func_ov027_020b7dfc(work->elements);
        DestroyFndObjectList_020014f0(work->altObjects);
    }
    ZeroHalfThenFree_0202cd78(work->containerA);
    ZeroHalfThenFree_0202cd78(work->containerB);
    REG_BG0CNT = (REG_BG0CNT & ~3) | 3;
    REG_BG1CNT = (REG_BG1CNT & ~3);
    REG_BG2CNT = (REG_BG2CNT & ~3) | 1;
    REG_BG3CNT = (REG_BG3CNT & ~3) | 2;
    G3X_SetClearColor_02006c08(0, 0x1f, 0x7fff, 0x3f, FALSE);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0xf00;
    SetMenuGaugeActive_0207512c(0, work->gaugeEnabled);
    data_ov045_020c0880 = NULL;
}
