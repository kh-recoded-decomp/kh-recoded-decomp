#include "nitro/types.h"

typedef struct VramBlock {
    u32 pad00;
    u32 size;
    u8 pad08[0x30];
    int offsets[10];
    struct VramBlock *next;
} VramBlock;

typedef struct VramManager {
    u8 pad[0x460c];
    u32 firstFree;
    u8 pad4610[8];
    VramBlock *head;
} VramManager;

typedef struct VramRequest {
    u8 pad[0x10];
    u32 size;
} VramRequest;

int func_0204e588(VramManager *manager);
int IntArray_Get_020152b0(int *array, int index);

u32 FindFreeVramGapOffset_0204e65c(VramManager *manager, VramRequest *request)
{
    VramBlock *block = manager->head;
    int mode;
    u32 result = manager->firstFree;
    mode = func_0204e588(manager);

    /* First gap large enough, else after the last block */
    while (block != NULL) {
        u32 offset = IntArray_Get_020152b0(block->offsets, mode);
        u32 end;
        u32 nextOffset;
        if (block->next == NULL) {
            result = offset + block->size;
            break;
        }
        nextOffset = IntArray_Get_020152b0(block->next->offsets, mode);
        end = offset + block->size;
        if (request->size <= nextOffset - end) {
            result = end;
            break;
        }
        block = block->next;
    }
    return result;
}


