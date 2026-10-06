#include "nitro/types.h"

extern u32 data_ov002_0206c464;
extern void ClosePanelSelectorAll(void);
extern void DrawMenuLabels(void);

void func_ov002_02064fd4(void) {
    ClosePanelSelectorAll();
    DrawMenuLabels();
    *(u32 *)(data_ov002_0206c464 + 8) = 0;
}
