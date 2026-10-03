#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_0000[0x69e8];
    u8 panel[1];
} MenuContext;

extern MenuContext *g_context_0206c464;
extern void func_ov027_020b9098(void *panel, void (*callback)(void));
extern void func_ov002_02065c54(void);

void ReleaseMenuPanelCallback_02065bf4(void)
{
    func_ov027_020b9098(g_context_0206c464->panel, func_ov002_02065c54);
}
