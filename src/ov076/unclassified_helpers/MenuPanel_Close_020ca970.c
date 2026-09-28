#include "nitro/types.h"

typedef struct MenuPanel MenuPanel;

extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void MenuPanel_Finish_020c9c5c(MenuPanel *panel, BOOL confirmed);

int MenuPanel_Close_020ca970(MenuPanel *panel)
{
    PlaySoundEffect_0204d924(1, 3);
    MenuPanel_Finish_020c9c5c(panel, TRUE);
    return 3;
}
