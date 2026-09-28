#include "nitro/types.h"

extern void func_0202a1c4(void *block);

typedef struct {
    s32 count0;
    u8 *list0;
    s32 count1;
    u8 *list1;
    void *single;
} RecordLists;

void FreeRecordListsAndBuffer_020a7f00(RecordLists *obj)
{
    s32 i;

    if (obj->single != 0) {
        func_0202a1c4(obj->single);
        obj->single = 0;
    }
    if (obj->list1 != 0) {
        for (i = 0; i < obj->count1; i++) {
            void *sub = *(void **)(obj->list1 + i * 0x10 + 8);
            if (sub != 0) {
                func_0202a1c4(sub);
            }
        }
        func_0202a1c4(obj->list1);
        obj->list1 = 0;
        obj->count1 = 0;
    }
    if (obj->list0 != 0) {
        for (i = 0; i < obj->count0; i++) {
            func_0202a1c4(*(void **)(obj->list0 + i * 8 + 4));
        }
        func_0202a1c4(obj->list0);
        obj->list0 = 0;
        obj->count0 = 0;
    }
}
