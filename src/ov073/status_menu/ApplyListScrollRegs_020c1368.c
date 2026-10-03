#include "nitro/types.h"

typedef struct ListView {
    u8 pad_000[0x178];
    BOOL rootDirty;
    BOOL applying;
} ListView;

extern ListView *data_ov073_020c4240;
extern int GetListBgHOffset_020c3f9c(ListView *list);
extern void *func_ov039_020bc1cc(void);
extern void UpdateWidgetRootAndFireAlarm_020b8c94(void *root, int keys);

void ApplyListScrollRegs_020c1368(void)
{
    int offset = GetListBgHOffset_020c3f9c(data_ov073_020c4240);
    void *root = func_ov039_020bc1cc();

    if (data_ov073_020c4240->applying == 0) {
        data_ov073_020c4240->applying = 1;
        offset &= 0x1ff;
        *(vu32 *)0x04001018 = offset;
        *(vu32 *)0x0400101c = offset;
        if (data_ov073_020c4240->rootDirty) {
            UpdateWidgetRootAndFireAlarm_020b8c94(root, 0);
            data_ov073_020c4240->rootDirty = FALSE;
        }
        data_ov073_020c4240->applying = 0;
    }
}
