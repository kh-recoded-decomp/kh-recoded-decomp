#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd0a0];
    u32 pageState;
} ResultsContext;

extern ResultsContext *gResultsPageContextStorage;

u32 GetResultsPageState(void)
{
    return gResultsPageContextStorage->pageState;
}
