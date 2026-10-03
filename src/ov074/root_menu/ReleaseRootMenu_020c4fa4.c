#include "nitro/types.h"

#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)

typedef struct RenderObj {
    u32 flag;
    u8 pad_04[0x30];
    void *cbFunc;
    void *cbInitFunc;
} RenderObj;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct RootMenu {
    u8 pad_00[8];
    BOOL isFullMenu;
    u8 pad_0c[8];
    int textureKeyA;
    int textureKeyB;
    u8 model[0x20];
    RenderObj renderObj;
    u8 pad_78[0x120 - 0x78];
    u8 weapon[0x230];
    u8 animA[0x24];
    u8 animB[0x24];
    u8 pad_398[0x438 - 0x398];
    TextWindow windows[4];
    u8 pad_508[0x5dc - 0x508];
    u8 strings[0xc];
} RootMenu;

extern void *func_ov039_020bc1bc(void);
extern int func_ov039_020bc18c(void);
extern void SweepElements_020b831c(int context);
extern void DestroyAllContainerElements_020b900c(void *container);
extern void ReleaseIfMarked_020b903c(void *container);
extern void ClearSbcCallback_020188b8(RenderObj *renderObj);
extern void ReleaseModelSet_020a9928(void *weapon);
extern void ReleaseResourceAndDetach_0202eee8(void *model);
extern void func_0202eaf4(void *anim);
extern void ZeroHalfThenFree_0202cd78(int key);
extern void FreeSharedBuffers_020a9568(void);
extern void func_02006d3c(int value);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);
extern void FreePointerIfSet_020ba294(void *table);
extern void DestroyFndObjectList_020014f0(TextWindow *window);

void ReleaseRootMenu_020c4fa4(RootMenu *menu)
{
    void *container = func_ov039_020bc1bc();

    SweepElements_020b831c(func_ov039_020bc18c());
    DestroyAllContainerElements_020b900c(container);
    ReleaseIfMarked_020b903c(container);
    if (menu->isFullMenu) {
        ClearSbcCallback_020188b8(&menu->renderObj);
        menu->renderObj.cbFunc = NULL;
        if (menu->renderObj.cbInitFunc == NULL) {
            menu->renderObj.flag &= ~1;
        }
        ReleaseModelSet_020a9928(menu->weapon);
        ReleaseResourceAndDetach_0202eee8(menu->model);
        func_0202eaf4(menu->animB);
        func_0202eaf4(menu->animA);
        ZeroHalfThenFree_0202cd78(menu->textureKeyB);
        ZeroHalfThenFree_0202cd78(menu->textureKeyA);
        FreeSharedBuffers_020a9568();
    }
    func_02006d3c(0);
    REG_BG0CNT = REG_BG0CNT & ~3;
    REG_BG1CNT = (REG_BG1CNT & ~3) | 1;
    REG_BG2CNT = (REG_BG2CNT & 0x43) | 0x1e00;
    NNS_GfdResetFrmTexVramState_0201391c();
    func_02013d74();
    FreePointerIfSet_020ba294(menu->strings);
    DestroyFndObjectList_020014f0(&menu->windows[3]);
    DestroyFndObjectList_020014f0(&menu->windows[0]);
    DestroyFndObjectList_020014f0(&menu->windows[1]);
    DestroyFndObjectList_020014f0(&menu->windows[2]);
}
