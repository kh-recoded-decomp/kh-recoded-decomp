#include "nitro/types.h"

typedef struct Panel Panel;

extern void func_ov000_02061bf4(Panel *panel, BOOL flag);
extern u32 func_0202b788(void);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

void func_ov000_0206276c(Panel *panel)
{
    func_ov000_02061bf4(panel, TRUE);
    WriteGlobalPackedBits_02027360(0x1a02, 3, func_0202b788());
}
