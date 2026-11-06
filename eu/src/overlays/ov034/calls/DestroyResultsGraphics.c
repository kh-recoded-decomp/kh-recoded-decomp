#include "nitro/types.h"

extern u32 gResultsScreenPointersPrefix[2];
#define resultsWork ((int)gResultsScreenPointersPrefix[1])
extern u32 DestroyFndObjectList();
extern u32 FreePointerIfSet();
extern u32 NotifyBothOrOne();
extern u32 FreeResourceBufferAndProbeHeap();
extern u32 ReleaseRecordSlot();
extern u32 FreeTagTrackerPools();
extern u32 DestroyObjectsAndRelease();

void DestroyResultsGraphics(void)
{
    NotifyBothOrOne(1, 0x020c0f10, 0);
    ReleaseRecordSlot(0);
    FreePointerIfSet((void *)(resultsWork + 0x6b3c));
    DestroyFndObjectList(resultsWork + 0x6b60);
    FreeResourceBufferAndProbeHeap(resultsWork + 0x6b48);
    FreeResourceBufferAndProbeHeap(resultsWork + 0x6b54);
    FreeTagTrackerPools(resultsWork + 0x10);
    DestroyObjectsAndRelease(resultsWork + 0x5c);
    return;
}
