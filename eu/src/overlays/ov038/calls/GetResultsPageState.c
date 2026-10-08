#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd0a0];
    u32 pageState;
} ResultsContext;

extern ResultsContext *data_ov038_020bd164;

u32 GetResultsPageState(void)
{
    return data_ov038_020bd164->pageState;
}
