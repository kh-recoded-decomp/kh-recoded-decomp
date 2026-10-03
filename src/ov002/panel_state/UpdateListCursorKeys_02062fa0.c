#include "nitro/types.h"

extern u32 UpdateListCursor_02062fb4(void *input, void *list, u32 keys);

u32 UpdateListCursorKeys_02062fa0(u32 keys, void *list)
{
    return UpdateListCursor_02062fb4(NULL, list, keys);
}
