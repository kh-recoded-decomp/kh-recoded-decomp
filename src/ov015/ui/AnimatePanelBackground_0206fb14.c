#include "nitro/types.h"

typedef struct PanelContext {
    s8 screenMode;
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern void func_ov015_0206fb6c(void);
extern void AnimateBg1CenterTiles_0206fcd8(void);
extern void AnimateBg1EdgeBandTiles_0206fe44(void);

void AnimatePanelBackground_0206fb14(void)
{
    switch (data_ov015_0207e960->screenMode) {
    case 0:
    case 1:
    case 7:
        func_ov015_0206fb6c();
        break;
    case 2:
    case 3:
    case 6:
        AnimateBg1CenterTiles_0206fcd8();
        break;
    case 5:
        AnimateBg1EdgeBandTiles_0206fe44();
        break;
    case 4:
        break;
    }
}
