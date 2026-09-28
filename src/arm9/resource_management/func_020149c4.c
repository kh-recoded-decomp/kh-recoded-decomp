#include "nitro/types.h"

typedef struct {
    void *usedListHead;
    void *freeListHead;
    u32 param1;
    u32 bufferBase;
    u32 bufferSize;
} TableManagerFields;

extern TableManagerFields g_tableFields_0205a900;
extern void *data_0205a900;
extern void *data_0205a904;

extern void *func_020141e8(void *nodes, u32 count);
extern void func_020141dc(u32 argument0);
extern void func_0201422c(void *usedListHeadPtr, void *freeListHeadPtr, u32 arg2, u32 param1);
extern void func_020143d4(void *usedListHeadPtr, void *freeListHeadPtr);

void func_020149c4(void)
{
    g_tableFields_0205a900.freeListHead =
        func_020141e8((void *)g_tableFields_0205a900.bufferBase, g_tableFields_0205a900.bufferSize >> 4);
    func_020141dc((u32)&data_0205a900);
    func_0201422c(&data_0205a900, &data_0205a904, 0, g_tableFields_0205a900.param1);
    func_020143d4(&data_0205a900, &data_0205a904);
}
