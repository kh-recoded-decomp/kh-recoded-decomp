/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The native word is the key of the registered session callback. */
extern void RefreshActiveMenuObjects(void);

extern void *GetRunningTaskWork(void);
extern void ReleaseTargetSpritePairResources(int base);
extern void ReleaseTargetCursorResources(int base);
extern void RemoveTaggedListEntries(u32 address);

extern u32 gFieldTargetSelectionWork;

void ShutdownSceneWork(void)
{
    int heap;

    heap = (int)GetRunningTaskWork();
    ReleaseTargetSpritePairResources(heap + 0x50);
    ReleaseTargetCursorResources(heap + 0xcc);
    RemoveTaggedListEntries((u32)RefreshActiveMenuObjects);
    gFieldTargetSelectionWork = 0;
}
