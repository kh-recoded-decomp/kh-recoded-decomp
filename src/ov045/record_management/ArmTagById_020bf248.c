#include "nitro/types.h"

extern void *FindLoadedElementById_020b8390(void *list, u16 id);
extern void SetTagRecordArmed_020b83e8(void *tracker, void *record, BOOL arm);
extern void func_ov027_020b845c(void *tracker, void *record);

void ArmTagById_020bf248(void *tracker, int id)
{
    void *record = FindLoadedElementById_020b8390(tracker, id);

    SetTagRecordArmed_020b83e8(tracker, record, TRUE);
    func_ov027_020b845c(tracker, record);
}

