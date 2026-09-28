#include "nitro/types.h"

typedef int (*PanelCallback)(void *arg);

extern void setDualArrayEntry_02025448(int slot, PanelCallback callback, void *arg);
extern int func_020285a0(void *arg);
extern int func_0202867c(void *arg);
extern int func_0202874c(void *arg);

void RegisterPanelCallbacks_02028548(void)
{
    setDualArrayEntry_02025448(0, func_020285a0, NULL);
    setDualArrayEntry_02025448(1, func_0202867c, NULL);
    setDualArrayEntry_02025448(2, func_0202874c, NULL);
}
