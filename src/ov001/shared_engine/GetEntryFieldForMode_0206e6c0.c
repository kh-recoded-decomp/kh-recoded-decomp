#include "nitro/types.h"

typedef struct EventContext {
    s32 mode;
} EventContext;

extern EventContext *g_eventContext_020a049c;
extern u32 GetBoundedEntryField_0206db5c(int index);

u32 GetEntryFieldForMode_0206e6c0(int index)
{
    switch (g_eventContext_020a049c->mode) {
    case 0:
    case 2:
        return GetBoundedEntryField_0206db5c(index) + 0x230;
    case 1:
        return GetBoundedEntryField_0206db5c(index) + 0x230;
    }
    return 0;
}
