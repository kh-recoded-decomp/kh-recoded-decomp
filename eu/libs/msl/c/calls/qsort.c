#include "nitro/types.h"

typedef int (*SortCompare)(const void *, const void *);

static inline void SwapElements(u8 *right, u8 *left, u32 size)
{
    while (size != 0) {
        u8 leftByte = *left;
        u8 rightByte = *right;
        size--;
        *right++ = leftByte;
        *left++ = rightByte;
    }
}

/* The runtime qsort uses an in-place binary heap, with one-based indices. */
void qsort(void *base, u32 count, u32 size, SortCompare compare)
{
    u8 *array = base;
    u32 root;
    u8 *first;
    u8 *last;
    if (count < 2) {
        return;
    }
    root = count / 2 + 1;
    first = array + size * (root - 1);
    last = array + size * (count - 1);
    for (;;) {
        if (root > 1) {
            root--;
            first -= size;
        } else {
            SwapElements(first, last, size);
            count--;
            if (count == 1) {
                return;
            }
            last -= size;
        }
        {
            u32 index = root;
            u8 *child = array + size * (root - 1);
            while (count >= index * 2) {
                u8 *parent = child;
                index *= 2;
                child = array + size * (index - 1);
                if (count > index && compare(child, child + size) < 0) {
                    index++;
                    child += size;
                }
                if (compare(parent, child) >= 0) {
                    break;
                }
                SwapElements(parent, child, size);
            }
        }
    }
}
