#include "nitro/types.h"

extern void *FindLoadedElementById_020b8390(void *list, u16 id);
extern void SetTagRecordArmed_020b83e8(void *tracker, void *record, BOOL arm);

void DisarmTagById_020bf26c(void *tracker, int id)
{
    SetTagRecordArmed_020b83e8(tracker, FindLoadedElementById_020b8390(tracker, id), FALSE);
}

