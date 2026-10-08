#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitSessionCallbackList(void);
extern void RemoveAllTaggedListEntries(void);

void *gSessionTaskClassDescriptor[5] = {
    (void *)0x00110012,
    (void *)InitSessionCallbackList,
    (void *)RemoveAllTaggedListEntries,
    NULL,
    NULL,
};
