#include "nitro/types.h"

extern int data_02056b50[];

int AllocateNextThreadId_0200249c(void)
{
    return ++data_02056b50[6];
}
