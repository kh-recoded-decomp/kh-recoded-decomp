#include "nitro/types.h"

typedef struct PanelElement {
    u8 pad_00[0xc];
    u32 value;
} PanelElement;

typedef struct MenuSelectionContext {
    u8 pad_00[0xc];
    u32 selectedValue;
} MenuSelectionContext;

extern MenuSelectionContext *g_context_0206c464;
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void UpdateMenuSelectionSound(PanelElement *element)
{
    u32 previousValue = g_context_0206c464->selectedValue;

    g_context_0206c464->selectedValue = element->value;
    if (g_context_0206c464->selectedValue != previousValue) {
        PlaySoundEffect_0204d924(2, 0);
    }
}
