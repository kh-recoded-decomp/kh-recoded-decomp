#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6690];
    u32 lookup;
} Panel;

extern u16 func_0202b788(void);
extern void func_02027360(int opcode, int channel, u16 value);
extern u32 func_0202a448(void *table, int index);
extern int func_0204ded4(int flag);
extern void func_0204dd4c(int param1, int param2);

extern u32 data_ov000_020639b8;

void UpdatePanelLookup_02062c08(Panel *panel)
{
    u16 value = func_0202b788();

    func_02027360(0x1a02, 3, value);
    panel->lookup = func_0202a448(&data_ov000_020639b8, 0);
    if (func_0204ded4(0) != 0) {
        return;
    }
    func_0204dd4c(0, 0);
}
