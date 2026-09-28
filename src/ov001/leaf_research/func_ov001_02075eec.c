#include "nitro/types.h"

extern void *func_ov027_020b8184(void *table, u32 id);
extern void InvokeCallback40_020b8268(void *table, void *entry);
extern void *func_ov027_020b8390(void *table, u32 id);
extern void func_ov027_020b83e8(void *table, void *entry, u32 flag);

void func_ov001_02075eec(u32 self, void *table)
{
    void *entry;

    entry = func_ov027_020b8390(table, 10);
    func_ov027_020b83e8(table, entry, 0);
    entry = func_ov027_020b8390(table, 0xb);
    func_ov027_020b83e8(table, entry, 0);
    entry = func_ov027_020b8390(table, 0xc);
    func_ov027_020b83e8(table, entry, 0);
    entry = func_ov027_020b8390(table, 0x11);
    func_ov027_020b83e8(table, entry, 0);
    entry = func_ov027_020b8390(table, 0x12);
    func_ov027_020b83e8(table, entry, 0);
    entry = func_ov027_020b8184(table, 0x55);
    InvokeCallback40_020b8268(table, entry);
}
