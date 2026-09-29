#include "nitro/types.h"

typedef struct PanelElement {
    u8 pad_00[0xc];
    u32 value;
} PanelElement;

typedef struct MenuContext {
    u8 unk_00;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[4];
    s32 unk_08;
    u32 currentValue;
    u8 pad_10[0x69e8 - 0x10];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *g_context_0206c464;

extern PanelElement *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9580(void *panel, PanelElement *element, BOOL visible);
extern void func_ov027_020b96e4(void *panel, PanelElement *element);
extern void func_ov027_020b9764(void *panel, PanelElement *element, BOOL enabled);
extern void func_ov027_020b95e4(void *panel, PanelElement *element);
extern void func_ov027_020b9098(void *panel, void (*callback)(PanelElement *element));
extern void func_ov002_02064584(int state);
extern void func_ov002_02064c9c(int state);
extern void func_ov002_02065d54(PanelElement *element);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void OpenMenuPopup_0206574c(void)
{
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    func_ov027_020b9580(g_context_0206c464->panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xb), TRUE);
    func_ov027_020b9580(g_context_0206c464->panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xc), TRUE);
    func_ov002_02064584(1);
    func_ov027_020b96e4(g_context_0206c464->panel, func_ov027_020b90a4(g_context_0206c464->panel, 0xc));
    func_ov027_020b9764(g_context_0206c464->panel,
                        func_ov027_020b90a4(g_context_0206c464->panel, g_context_0206c464->selectedIndex + 1), TRUE);
    func_ov027_020b95e4(g_context_0206c464->panel,
                        func_ov027_020b90a4(g_context_0206c464->panel, g_context_0206c464->selectedIndex + 1));
    func_ov027_020b9098(g_context_0206c464->panel, func_ov002_02065d54);
    g_context_0206c464->currentValue = func_ov027_020b90a4(g_context_0206c464->panel, 0xc)->value;
    PlaySoundEffect_0204d924(2, 3);
    func_ov002_02064c9c(0);
    g_context_0206c464->unk_02 = 0;
    g_context_0206c464->unk_08 = 0;
}
