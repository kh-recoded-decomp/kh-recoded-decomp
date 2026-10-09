#include "nitro/types.h"

typedef struct MenuSelectionContext {
    u8 pad_00[2];
    s8 selection;
} MenuSelectionContext;

extern MenuSelectionContext *g_context_0206c464;

void SetMenuSelection2(void)
{
    g_context_0206c464->selection = 2;
}
