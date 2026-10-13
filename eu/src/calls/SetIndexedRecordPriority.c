/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
#include "nitro/types.h"

typedef struct PriorityLink {
    void *previous;
    void *next;
} PriorityLink;

typedef struct IndexedPriorityRecord {
    u32 reserved00;
    PriorityLink link;
    s32 sortKey;
    u8 reserved10[0x7c];
} IndexedPriorityRecord;

extern void PrioList_Resort(IndexedPriorityRecord *records, PriorityLink *link,
                            PriorityLink *head, IndexedPriorityRecord *record);

/* Convert a priority to its sort key and relink the indexed record.
 * This caller supplies two additional bookkeeping arguments in the original
 * ABI; PrioList_Resort currently only consumes the list and link arguments. */
void SetIndexedRecordPriority(IndexedPriorityRecord *records, int index, int priority)
{
    PriorityLink *link;
    if (index < 0) {
        return;
    }
    link = (PriorityLink *)((u8 *)&records->link + index * sizeof(*records));
    records[index].sortKey = priority * -0x800;
    PrioList_Resort(records, link, &records->link, &records[index]);
}
