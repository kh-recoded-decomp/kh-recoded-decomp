#include "nitro/types.h"

extern void Element_RunStopHook(void *node);
extern u32 gFieldEntryPoolManager;

void StopAndClearFieldEntryList(void) {
    u32 base = gFieldEntryPoolManager;
    void **node = *(void ***)(base + 8);
    while (node != 0) {
        Element_RunStopHook(node);
        node = *node;
    }
    *(u32 *)(base + 8) = 0;
    *(u32 *)(base + 0xc) = 0;
    *(u16 *)(base + 6) = 0;
}
