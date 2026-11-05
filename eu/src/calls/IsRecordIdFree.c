#include "src/filesystem/FileLoaderState.h"

extern struct {
    u8 pad_00[4];
    u8 *field_4;
} gFileLoader;

extern unsigned long long _s32_div_f(u32 a, u32 b);

BOOL IsRecordIdFree(int id)
{
    u8 *fieldPtr = gFileLoader.field_4;
    FileLoaderMessageQueue *queue = &gFileLoaderMessageQueue;
    int current = *(int *)(fieldPtr + 0x448);
    int count;
    int i;

    if (id == 0) {
        return queue->count == 0 && current == 0;
    }
    if (current != 0 && *(int *)((u8 *)current + 0x28) == id) {
        return FALSE;
    }
    count = queue->count;
    i = 0;
    if (count > 0) {
        void **table = queue->table;
        u32 head = queue->head;
        u32 capacity = queue->capacity;
        do {
            u32 index = (u32)(_s32_div_f(i + head, capacity) >> 32);
            int entry = (int)table[index];
            if (entry != 0 && *(int *)((u8 *)entry + 0x28) == id) {
                return FALSE;
            }
            i++;
        } while (i < count);
    }
    return TRUE;
}
