#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/fnd.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

NNSiFndUntHeapMBlockHead * PopMBlock_0201360c (NNSiFndUntMBlockList * list)
{
    NNSiFndUntHeapMBlockHead * block = list->head;

    if (block) {
        list->head = block->pMBlkHdNext;
    }

    return block;
}
