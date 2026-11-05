#include "nitro/types.h"

void SetWidgetRootInputCallback(void *obj, u32 value) {
    *(u32 *)((u8 *)obj + 0x644c) = value;
}
