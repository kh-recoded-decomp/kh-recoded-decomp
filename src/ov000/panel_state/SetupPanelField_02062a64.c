#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6674];
    u32 count;
    void *field;
} Panel;

extern void func_02026ee0(u32 mode);
extern void *func_0202a448(void *descriptor, void *userData);
extern u32 data_ov000_020639a4;

void SetupPanelField_02062a64(Panel *panel)
{
    func_02026ee0(1);
    panel->count = 0;
    panel->field = func_0202a448(&data_ov000_020639a4, NULL);
}
