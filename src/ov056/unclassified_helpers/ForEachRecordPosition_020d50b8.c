#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*RecordFilter)(s32 recordId, void *userData);
typedef BOOL (*RecordVisitor)(s32 recordId, VecFx32 *position, void *userData);

extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 recordId);
extern BOOL func_ov001_02087bec(s32 recordId, u16 cursor, VecFx32 *position, u16 *nextCursor);

void ForEachRecordPosition_020d50b8(RecordFilter filter, RecordVisitor visitor, void *userData)
{
    s32 recordId;
    u16 cursor;
    VecFx32 position;
    BOOL result;

    for (recordId = func_ov001_02087928(); recordId != 0; recordId = func_ov001_02087944(recordId)) {
        if (filter != NULL) {
            result = filter(recordId, userData);
        } else {
            result = TRUE;
        }
        if (result) {
            cursor = 0;
            do {
                if (func_ov001_02087bec(recordId, cursor, &position, &cursor)) {
                    if (visitor != NULL) {
                        result = visitor(recordId, &position, userData);
                    } else {
                        result = FALSE;
                    }
                    if (result) {
                        return;
                    }
                }
            } while (cursor != 0);
        }
    }
}
