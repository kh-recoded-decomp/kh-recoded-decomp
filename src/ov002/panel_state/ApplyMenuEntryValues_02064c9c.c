#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[0x22];
    u8 flags_b0 : 1;
    u8 hideEntry2 : 1;
    u8 flags_b2 : 6;
    u8 pad_23[0x69e8 - 0x23];
    u8 panel[4];
} MenuContext;

extern MenuContext *g_context_0206c464;
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void ApplySelectedSubitemValues_020b94fc(void *panel, void *element, int useAlt);

void ApplyMenuEntryValues_02064c9c(int useAlt)
{
    void *panel;

    panel = g_context_0206c464->panel;
    ApplySelectedSubitemValues_020b94fc(panel, func_ov027_020b90a4(panel, 1), useAlt);
    if (!g_context_0206c464->hideEntry2) {
        panel = g_context_0206c464->panel;
        ApplySelectedSubitemValues_020b94fc(panel, func_ov027_020b90a4(panel, 2), useAlt);
    }
    panel = g_context_0206c464->panel;
    ApplySelectedSubitemValues_020b94fc(panel, func_ov027_020b90a4(panel, 3), useAlt);
    panel = g_context_0206c464->panel;
    ApplySelectedSubitemValues_020b94fc(panel, func_ov027_020b90a4(panel, 4), useAlt);
}
