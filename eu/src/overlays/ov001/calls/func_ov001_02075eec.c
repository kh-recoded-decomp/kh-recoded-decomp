#include "nitro/types.h"

extern void *FindActiveRecordById(void *table, u32 id);
extern void func_ov027_020b8288(void *table, void *entry);
extern void *FindLoadedElementById(void *table, u32 id);
extern void SetTagRecordArmed(void *table, void *entry, u32 flag);

void func_ov001_02075eec(u32 self, void *table)
{
    void *entry;

    entry = FindLoadedElementById(table, 10);
    SetTagRecordArmed(table, entry, 0);
    entry = FindLoadedElementById(table, 0xb);
    SetTagRecordArmed(table, entry, 0);
    entry = FindLoadedElementById(table, 0xc);
    SetTagRecordArmed(table, entry, 0);
    entry = FindLoadedElementById(table, 0x11);
    SetTagRecordArmed(table, entry, 0);
    entry = FindLoadedElementById(table, 0x12);
    SetTagRecordArmed(table, entry, 0);
    entry = FindActiveRecordById(table, 0x55);
    func_ov027_020b8288(table, entry);
}
