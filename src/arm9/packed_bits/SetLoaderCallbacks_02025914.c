#include "nitro/types.h"

extern void func_02027348(void);
extern void func_02027360(void);

void SetLoaderCallbacks_02025914(int context, int writeHandler, int readHandler)
{
    if (writeHandler != 0) {
        *(int *)(context + 0x644) = writeHandler;
    } else {
        *(int *)(context + 0x644) = (int)func_02027360;
    }

    if (readHandler != 0) {
        *(int *)(context + 0x640) = readHandler;
        return;
    }
    *(int *)(context + 0x640) = (int)func_02027348;
}
