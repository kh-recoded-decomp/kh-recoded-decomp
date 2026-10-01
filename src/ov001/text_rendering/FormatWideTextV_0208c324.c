#include "nitro/types.h"

typedef char *VaList;

extern int Text_VSNPrintfWide_0202e09c(u16 *dest, u32 destLength, const u16 *format, VaList args);

u16 *FormatWideTextV_0208c324(const u16 *format, u16 *dest, u32 destLength, VaList args)
{
    Text_VSNPrintfWide_0202e09c(dest, destLength, format, args);
    return dest;
}
