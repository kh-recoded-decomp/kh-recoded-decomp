#include "nitro/types.h"

extern void *FindLoadedElementById_020b8390(void *list, u16 id);
extern void PositionListRecords_020b8498(void *container, void *list, s16 position);
extern void SetTagRecordArmed_020b83e8(void *tracker, void *record, BOOL arm);
extern void func_ov027_020b845c(void *tracker, void *record);

void ArmTagAtPosition_020bf218(void *tracker, int id, int position)
{
    void *record = FindLoadedElementById_020b8390(tracker, id);

    PositionListRecords_020b8498(tracker, record, position);
    SetTagRecordArmed_020b83e8(tracker, record, TRUE);
    func_ov027_020b845c(tracker, record);
}
