#include "nitro/types.h"

typedef struct Panel Panel;

extern void ApplyPanelMenuFlags(Panel *panel, BOOL flag);
extern u32 GetLanguageIndex(void);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

void ApplyTitleMenuFlagsAndStoreLanguage(Panel *panel)
{
    ApplyPanelMenuFlags(panel, TRUE);
    WriteGlobalPackedBits(0x1a02, 3, GetLanguageIndex());
}
