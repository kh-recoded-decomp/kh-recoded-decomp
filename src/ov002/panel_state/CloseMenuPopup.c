#include "nitro/types.h"

typedef struct PanelElement PanelElement;

typedef struct MenuContext {
    u8 state;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[0x69e8 - 4];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *g_context_0206c464;

extern void func_ov002_020643a0(void);
extern PanelElement *func_ov027_020b90a4(void *panel, int elementId);
extern void SetEntrySlotsVisible_020b9580(void *panel, PanelElement *element, BOOL visible);
extern void func_ov002_02064c9c(int state);
extern void func_ov027_020b96e4(void *panel, PanelElement *element);
extern void func_ov027_020b9620(void *panel, PanelElement *element);
extern void func_ov027_020b9098(void *panel, void (*callback)(void));
extern void OnPopupElementTouched(void);
extern void ReleaseMenuCursorState(void);

void CloseMenuPopup(void)
{
    void *panel;

    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1e00;
    func_ov002_020643a0();
    panel = g_context_0206c464->panel;
    SetEntrySlotsVisible_020b9580(panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xb), FALSE);
    panel = g_context_0206c464->panel;
    SetEntrySlotsVisible_020b9580(panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xc), FALSE);
    func_ov002_02064c9c(1);
    panel = g_context_0206c464->panel;
    func_ov027_020b96e4(panel, func_ov027_020b90a4(g_context_0206c464->panel, g_context_0206c464->selectedIndex + 1));
    panel = g_context_0206c464->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(g_context_0206c464->panel, g_context_0206c464->selectedIndex + 1));
    func_ov027_020b9098(g_context_0206c464->panel, OnPopupElementTouched);
    ReleaseMenuCursorState();
}
