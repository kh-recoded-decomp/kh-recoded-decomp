#include "nitro/types.h"

u32 GetReportTopMode(const void *work)
{
    return *(const u32 *)((const u8 *)work + 0xcc68);
}
