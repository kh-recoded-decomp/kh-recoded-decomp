#include "nitro/types.h"

struct NNSiFndHeapHead;
extern void *OS_AllocFromArenaLo(int arena, u32 size, u32 align);
extern struct NNSiFndHeapHead *CreateExpandedHeap_020130f0(void *startAddress, u32 size, u16 optionFlag);
extern u32 GetTableAEntry_0200367c(int index);
extern u32 GetTableBEntry_02003690(int index);

void CreateEngineHeaps_02029fb8(void **specialHeapOut, void **defaultHeapOut)
{
    void *specialHeap = OS_AllocFromArenaLo(0, 0xc2800, 0x10);
    specialHeap = CreateExpandedHeap_020130f0(specialHeap, 0xc2800, 0);
    u32 tableB = GetTableBEntry_02003690(0);
    u32 tableA = GetTableAEntry_0200367c(0);
    u32 defaultSize = (tableA & 0xfffffff0) - ((tableB + 0xf) & 0xfffffff0);
    void *defaultHeap = OS_AllocFromArenaLo(0, defaultSize, 0x10);
    defaultHeap = CreateExpandedHeap_020130f0(defaultHeap, defaultSize, 0);
    *specialHeapOut = specialHeap;
    *defaultHeapOut = defaultHeap;
}
