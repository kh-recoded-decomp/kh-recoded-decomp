#include "nitro/types.h"

typedef struct PanelElement PanelElement;

typedef struct MenuContext {
    u8 state;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[4];
    s32 phase;
    u8 pad_0C[0x69e8 - 0xc];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *g_context_0206c464;

extern PanelElement *func_ov027_020b90a4(void *panel, int elementId);
extern void SetEntrySlotsVisible_020b9580(void *panel, PanelElement *element, BOOL visible);
extern void func_ov002_02064c9c(int state);
extern void func_ov002_02064584(int state);
extern void func_ov027_020b96e4(void *panel, PanelElement *element);
extern void func_ov027_020b9764(void *panel, PanelElement *element, BOOL enabled);
extern void func_ov027_020b95e4(void *panel, PanelElement *element);
extern void func_ov027_020b9098(void *panel, void (*callback)(void));
extern void UpdateMenuSelectionSound_02065d54(void);
extern void func_ov002_020666c8(int value);

void OpenMenuSelector_02065244(void)
{
    void *panel;

    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    panel = g_context_0206c464->panel;
    SetEntrySlotsVisible_020b9580(panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xb), TRUE);
    panel = g_context_0206c464->panel;
    SetEntrySlotsVisible_020b9580(panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xc), TRUE);
    func_ov002_02064c9c(0);
    func_ov002_02064584(3);
    func_ov027_020b96e4(g_context_0206c464->panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xc));
    panel = g_context_0206c464->panel;
    func_ov027_020b9764(panel, func_ov027_020b90a4(g_context_0206c464->panel, g_context_0206c464->selectedIndex + 1), TRUE);
    panel = g_context_0206c464->panel;
    func_ov027_020b95e4(panel, func_ov027_020b90a4(g_context_0206c464->panel, g_context_0206c464->selectedIndex + 1));
    func_ov027_020b9098(g_context_0206c464->panel, UpdateMenuSelectionSound_02065d54);
    g_context_0206c464->phase = 0;
    g_context_0206c464->unk_02 = 0;
    func_ov002_020666c8(0);
}
