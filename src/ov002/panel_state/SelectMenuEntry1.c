#include "nitro/types.h"

typedef struct MenuEntryContext {
    s8 state;
    s8 result;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[0x69e8 - 4];
    u8 widgetManager[1];
} MenuEntryContext;

extern MenuEntryContext *g_context_0206c464;
extern void *func_ov027_020b90a4(void *target, int index);
extern void func_ov027_020b96e4(void *target, void *value);
extern void func_ov002_020643a0(void);
extern void ChangeMenuState(int state);
extern void PlaySoundEffect_0204d924(int seqArcNo, int index);

void SelectMenuEntry1(void)
{
    void *selected;

    g_context_0206c464->result = 2;
    g_context_0206c464->selectedIndex = 0;
    selected = func_ov027_020b90a4(g_context_0206c464->widgetManager, 1);
    func_ov027_020b96e4(g_context_0206c464->widgetManager, selected);
    func_ov002_020643a0();
    ChangeMenuState(4);
    PlaySoundEffect_0204d924(2, 1);
}
