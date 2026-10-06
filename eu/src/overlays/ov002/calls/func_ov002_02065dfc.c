#include "nitro/types.h"

extern u32 data_ov002_0206c464;
extern u32 FindWidgetById(u32 target, u32 index);
extern void SetFocusedWidget(u32 target, u32 value);
extern void DrawMenuLabels(void);
extern void func_ov002_02064f6c(u32 value);
extern void PlaySoundEffect(u32 a, u32 b);

void func_ov002_02065dfc(void) {
    u32 selected;

    *(u8 *)(data_ov002_0206c464 + 1) = 3;
    *(u8 *)(data_ov002_0206c464 + 3) = 1;
    selected = FindWidgetById(data_ov002_0206c464 + 0x69e8, 2);
    SetFocusedWidget(data_ov002_0206c464 + 0x69e8, selected);
    DrawMenuLabels();
    func_ov002_02064f6c(4);
    PlaySoundEffect(2, 1);
}
