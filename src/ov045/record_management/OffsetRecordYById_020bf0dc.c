#include "nitro/types.h"

typedef struct {
    u16 id;
    s16 x;
    s16 y;
} Record;

extern Record *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void func_ov027_020b822c(void *pool, Record *record, s16 x, s16 y);

void OffsetRecordYById_020bf0dc(void *pool, int recordId, int offsetY)
{
    Record *record = FindActiveRecordById_020b8184(pool, (u16)recordId);

    func_ov027_020b822c(pool, record, record->x, record->y + offsetY);
}
