#include "nitro/types.h"

typedef struct LoaderRequest {
    struct LoaderRequest *next;
    u8 pad_04[0x30 - 4];
} LoaderRequest;

typedef struct FileLoader {
    void *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
    u8 pad_14[0x18 - 0x14];
    LoaderRequest *freeList;
    LoaderRequest *pool;
} FileLoader;

extern FileLoader data_02060564;

extern struct {
    void **heap;
    void **defaultHeap;
} data_02060394;

extern void *NNSi_FndAllocFromExpHeapEx_0202a1e4(u32 size, void **heap);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void func_01ff8830(void *dst, int value, int size);
extern void func_0200b394(void *file);
extern void func_0202c184(void);
extern void func_0202c1c8(void);
extern void OS_InitMessageQueue(void *queue, void *msgArray, int count);
extern u8 message_queue_02060584;
extern void *data_02060664[0x40];
extern void func_02002898(void *thread, void (*entry)(void *), void *arg, void *stack, u32 stackSize,
                          u32 priority);
extern void OS_WakeupThreadDirect_02002b60(char *thread);
extern void func_0202ba44(void *arg);
extern u8 data_020605a4[];
extern u8 data_020569c8[];

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->tail = 0;
    queue->head = 0;
}

BOOL InitFileLoader_0202c20c(void)
{
    int i;

    if (data_02060564.work == 0) {
        data_02060564.work = NNSi_FndAllocFromExpHeapEx_0202a1e4(0x23c0, data_02060394.heap);
        func_01ff8830(data_02060564.work, 0, 0x23c0);
        data_02060564.reader = AllocFromHeapOrDefaultEx_0202a210(0x420, 0x20, data_02060394.heap);
        data_02060564.reader2 = AllocFromHeapOrDefaultEx_0202a210(0x460, 0x20, data_02060394.heap);
        func_0200b394((u8 *)data_02060564.reader2 + 0x400);
        data_02060564.pool = NNSi_FndAllocFromExpHeapEx_0202a1e4(0xc00, data_02060394.heap);

        for (i = 0; i < 0x40; i++) {
            data_02060564.pool[i].next = (i < 0x3f) ? &data_02060564.pool[i + 1] : 0;
        }

        data_02060564.freeList = data_02060564.pool;
        data_02060564.hookA = func_0202c184;
        data_02060564.hookB = func_0202c1c8;
        OS_InitMessageQueue(&message_queue_02060584, data_02060664, 0x40);

        OS_InitThreadQueue((OSThreadQueue *)((u8 *)data_02060564.reader2 + 0x44c));

        func_02002898(data_020605a4, func_0202ba44, 0, data_020569c8, 0x800, 0x11);
        OS_WakeupThreadDirect_02002b60((char *)data_020605a4);
    }
    return 1;
}
