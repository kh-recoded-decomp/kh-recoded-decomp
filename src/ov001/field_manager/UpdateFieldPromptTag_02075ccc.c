#include "nitro/types.h"

typedef struct RecordPool RecordPool;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern void *FindActiveRecordById_020b8184(RecordPool *pool, u32 recordId);
extern void func_ov027_020b822c(RecordPool *pool, void *record, u16 first, u16 second);
extern void func_ov027_020b8284(RecordPool *pool, void *record, int visible);
extern void TagTracker_InvokeCallback_020b8210(RecordPool *pool, void *record);

void UpdateFieldPromptTag_02075ccc(int unused, RecordPool *pool)
{
    void *record;

    if (!IsModeSetOrFlag370aClear_0207259c() || IsHudFlag7Set_020725bc() || IsFieldFlag10Set_020728c4()) {
        func_ov027_020b822c(pool, FindActiveRecordById_020b8184(pool, 0x1f), 0, 0x14);
    } else {
        record = FindActiveRecordById_020b8184(pool, 0x1f);
        func_ov027_020b8284(pool, record, 1);
        TagTracker_InvokeCallback_020b8210(pool, record);
    }
}
