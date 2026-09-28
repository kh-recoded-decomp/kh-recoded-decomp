typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

typedef int OSArenaId;
typedef int OSHeapHandle;
#define OS_ARENA_MAX 9

#define OFFSET(n, a)    (((u32) (n)) & ((a) - 1))
#define TRUNC(n, a)     (((u32) (n)) & ~((a) - 1))
#define ROUND(n, a)     (((u32) (n) + (a) - 1) & ~((a) - 1))

#define ALIGNMENT       32
#define MINOBJSIZE      (HEADERSIZE + ALIGNMENT)
#define HEADERSIZE      ROUND(sizeof(Cell), ALIGNMENT)

typedef struct Cell Cell;
typedef struct HeapDesc HeapDesc;

struct Cell {
    Cell *prev;
    Cell *next;
    long size;
};

struct HeapDesc {
    long size;
    Cell *free;
    Cell *allocated;
};

typedef struct {
    volatile OSHeapHandle currentHeap;
    int numHeaps;
    void *arenaStart;
    void *arenaEnd;
    HeapDesc *heapArray;
} OSHeapInfo;

extern void *data_02044590[OS_ARENA_MAX];
#define OSiHeapInfo data_02044590
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern Cell *DLAddFront(Cell *list, Cell *cell);
extern Cell *DLExtract(Cell *list, Cell *cell);

Cell * DLInsert (Cell * list, Cell * cell)
{
    Cell * prev;
    Cell * next;

    for (next = list, prev = NULL; next; prev = next, next = next->next) {
        if (cell <= next) {
            break;
        }
    }

    cell->next = next;
    cell->prev = prev;

    if (next) {
        next->prev = cell;
        if ((char *)cell + cell->size == (char *)next) {

            cell->size += next->size;
            cell->next = next = next->next;
            if (next) {
                next->prev = cell;
            }
        }
    }

    if (prev) {
        prev->next = cell;
        if ((char *)prev + prev->size == (char *)cell) {
            prev->size += cell->size;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
        }
        return list;
    } else {
        return cell;
    }
}
