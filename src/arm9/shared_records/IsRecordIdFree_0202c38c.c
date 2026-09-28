#include "nitro/types.h"

typedef struct MessageQueue {
    u8 pad_00[0x10];
    void **table;
    u32 capacity;
    u32 head;
    u32 count;
} MessageQueue;

extern struct {
    u8 pad_00[4];
    u8 *field_4;
} data_02060564;

extern MessageQueue message_queue_02060584;
extern unsigned long long func_02023dbc(u32 a, u32 b);

BOOL IsRecordIdFree_0202c38c(int id)
{
    u8 *fieldPtr = data_02060564.field_4;
    MessageQueue *queue = &message_queue_02060584;
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
            u32 index = (u32)(func_02023dbc(i + head, capacity) >> 32);
            int entry = (int)table[index];
            if (entry != 0 && *(int *)((u8 *)entry + 0x28) == id) {
                return FALSE;
            }
            i++;
        } while (i < count);
    }
    return TRUE;
}
