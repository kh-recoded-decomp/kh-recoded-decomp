#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OSThread {
    u8 _reserved0[0x70];
    u32 priority;
    u8 _reserved74[0x8];
    struct OSThread *prev;
    struct OSThread *next;
} OSThread;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

OSThread *OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *pCur;
    OSThread *pNext;
    OSThread *pPrev;

    for (pCur = queue->head; pCur != NULL; pCur = pNext) {
        pNext = pCur->next;
        if (pCur == thread) {
            pPrev = pCur->prev;
            if (queue->head == pCur) {
                queue->head = pNext;
            } else {
                pPrev->next = pNext;
            }
            if (queue->tail == pCur) {
                queue->tail = pPrev;
            } else {
                pNext->prev = pPrev;
            }
            break;
        }
    }

    return pCur;
}
