#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[0x69e8];
    u8 panel[4];
} MenuContext;

extern MenuContext *g_context_0206c464;
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void ApplySelectedSubitemValues_020b94fc(void *panel, void *element, int useAlt);
extern void func_ov027_020b95e4(void *panel, void *element);
extern void func_ov027_020b96a0(void *panel, void *element, int value);
extern void func_ov002_02066a68(void);

void CloseMenuElement5_020651c0(void)
{
    void *panel;

    panel = g_context_0206c464->panel;
    ApplySelectedSubitemValues_020b94fc(panel, func_ov027_020b90a4(panel, 5), 0);
    panel = g_context_0206c464->panel;
    func_ov027_020b95e4(panel, func_ov027_020b90a4(panel, 5));
    panel = g_context_0206c464->panel;
    func_ov027_020b96a0(panel, func_ov027_020b90a4(panel, 5), 0);
    func_ov002_02066a68();
}
