#include "nitro/types.h"

typedef struct MenuContext {
    s8 state;
    u8 confirmed;
    u8 pad_02[6];
    int phase;
    u8 pad_0C[0x16];
    u8 unk_22_0 : 4;
    u8 pendingSelect : 1;
    u8 unk_22_5 : 3;
    u8 pad_23[0x69e8 - 0x23];
    u8 panel[0xce2c - 0x69e8];
    u16 touchCursor;
} MenuContext;

extern MenuContext *g_context_0206c464;

extern void func_ov002_0206671c(void);
extern u16 GetMenuCursorTouch_02066b2c(int mode);
extern BOOL IsButtonBPressed_020632c8(void);
extern BOOL func_ov002_02066c58(void);
extern void func_ov002_02064f6c(int nextState);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u16 *func_ov002_02062000(void);
extern void func_ov027_020b8ca8(void *panel, u16 value);

void UpdateMenuTouchSelect_020650e0(void)
{
    func_ov002_0206671c();
    switch (g_context_0206c464->phase) {
    case 0:
        g_context_0206c464->touchCursor = GetMenuCursorTouch_02066b2c(0);
        g_context_0206c464->phase = 5;
        break;
    case 5:
        if (IsButtonBPressed_020632c8() || g_context_0206c464->pendingSelect) {
            g_context_0206c464->pendingSelect = 0;
            if (func_ov002_02066c58()) {
                func_ov002_02064f6c(3);
                return;
            }
            PlaySoundEffect_0204d924(2, 4);
            g_context_0206c464->confirmed = 1;
            func_ov002_02064f6c(4);
            return;
        }
        func_ov027_020b8ca8(g_context_0206c464->panel, *func_ov002_02062000());
        break;
    }
}
