#include "nitro/types.h"

typedef struct MenuState {
    void (*enter)(void);
    void (*update)(void);
    void (*exit)(void);
} MenuState;

typedef struct MenuContext {
    s8 state;
    s8 result;
    u8 pad_02[0x56c - 2];
    u8 listA[0x69e8 - 0x56c];
    u8 listB[4];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern MenuState gMenuIntroCallback[];
extern void ScrollMenuClouds(void);
extern void func_ov002_02064d54(void);
extern void NNS_FndInitListWithOffset0_0204f130(void *list);
extern u32 IsScreenFadeComplete(void);

int UpdateMenuContext(void)
{
    gMenuIntroCallback[data_ov002_0206c464->state].update();
    ScrollMenuClouds();
    func_ov002_02064d54();
    NNS_FndInitListWithOffset0_0204f130(data_ov002_0206c464->listA);
    NNS_FndInitListWithOffset0_0204f130(data_ov002_0206c464->listB);
    if (IsScreenFadeComplete()) {
        return data_ov002_0206c464->result;
    }
    return 0;
}
