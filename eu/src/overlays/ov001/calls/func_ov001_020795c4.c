#include "nitro/types.h"

extern u32 GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *table, u32 id);
extern void func_ov027_020b8288(void *table, void *entry);
extern void *FindLoadedElementById(void *table, u32 id);
extern void SetTagRecordArmed(void *table, void *entry, u32 flag);

void func_ov001_020795c4(void)
{
    void *table;
    void *entry;

    table = (void *)GetSceneTagTracker();
    entry = FindLoadedElementById(table, 5);
    SetTagRecordArmed(table, entry, 0);
    entry = FindActiveRecordById(table, 0x3c);
    func_ov027_020b8288(table, entry);
}
