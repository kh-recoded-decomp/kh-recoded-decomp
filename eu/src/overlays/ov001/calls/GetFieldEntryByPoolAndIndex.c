#include "nitro/types.h"

extern int GetFieldEntryPoolAtIndex(void);
extern u32 GetEntryPoolObjectAtIndex(int arg1, u32 arg2);

u32 GetFieldEntryByPoolAndIndex(u32 param1, u32 param2) {
    int obj = GetFieldEntryPoolAtIndex();
    if (obj != 0) {
        return GetEntryPoolObjectAtIndex(obj, param2);
    }
    return 0;
}
