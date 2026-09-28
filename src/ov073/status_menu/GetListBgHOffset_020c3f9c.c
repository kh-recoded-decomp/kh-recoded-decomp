#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x94];
    int scrollX;
} ListView;

int GetListBgHOffset_020c3f9c(ListView *list)
{
    return -list->scrollX;
}
