#include "nitro/types.h"

extern int UpdateMenuContext_02064328(void);
extern void SwitchPanelMode_02062cb8(int mode);

void DispatchMenuResult_02062d28(void)
{
    switch (UpdateMenuContext_02064328()) {
    case 0:
        break;
    case 1:
        SwitchPanelMode_02062cb8(1);
        break;
    case 2:
        SwitchPanelMode_02062cb8(2);
        break;
    case 3:
        SwitchPanelMode_02062cb8(3);
        break;
    case 4:
        break;
    case 5:
        SwitchPanelMode_02062cb8(5);
        break;
    case 6:
        SwitchPanelMode_02062cb8(6);
        break;
    }
}
