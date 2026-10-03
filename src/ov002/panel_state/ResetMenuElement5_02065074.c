#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0c[0x69e8 - 0xc];
    u8 panel[4];
} MenuContext;

extern MenuContext *g_context_0206c464;
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void ApplySelectedSubitemValues_020b94fc(void *panel, void *element, int useAlt);
extern void func_ov027_020b9620(void *panel, void *element);
extern void func_ov002_020666c8(u32 value);

void ResetMenuElement5_02065074(void)
{
    void *panel;

    panel = g_context_0206c464->panel;
    ApplySelectedSubitemValues_020b94fc(panel, func_ov027_020b90a4(panel, 5), 1);
    panel = g_context_0206c464->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 5));
    func_ov002_020666c8(0);
    g_context_0206c464->unk_08 = 0;
}
