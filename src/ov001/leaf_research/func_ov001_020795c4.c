#include "nitro/types.h"

extern u32 func_ov001_020711b0(void);
extern void *func_ov027_020b8184(void *table, u32 id);
extern void InvokeCallback40_020b8268(void *table, void *entry);
extern void *func_ov027_020b8390(void *table, u32 id);
extern void func_ov027_020b83e8(void *table, void *entry, u32 flag);

void func_ov001_020795c4(void)
{
    void *table;
    void *entry;

    table = (void *)func_ov001_020711b0();
    entry = func_ov027_020b8390(table, 5);
    func_ov027_020b83e8(table, entry, 0);
    entry = func_ov027_020b8184(table, 0x3c);
    InvokeCallback40_020b8268(table, entry);
}
