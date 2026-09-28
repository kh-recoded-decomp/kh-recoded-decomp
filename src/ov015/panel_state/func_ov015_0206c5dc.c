#include "nitro/types.h"

typedef struct {
    u8 pad0_2 : 3;
    u8 flag3 : 1;
    u8 pad4_6 : 3;
    u8 flag7 : 1;
} PanelFlagsE1;

typedef struct {
    u8 pad0 : 1;
    u8 flag1 : 1;
    u8 pad2_3 : 2;
    u8 flag4 : 1;
    u8 pad5_7 : 3;
} PanelFlagsE2;

extern s8 *data_ov015_0207e960;
extern void func_ov015_02075338(void);
extern void func_ov015_02072c48(void);
extern void func_ov015_020702fc(void);
extern void func_ov015_0206fb14(void);
extern void func_ov015_02070540(void);

void func_ov015_0206c5dc(void) {
    if (data_ov015_0207e960[0] == 5) {
        func_ov015_02075338();
    }
    if (((PanelFlagsE2 *)(data_ov015_0207e960 + 0xe2))->flag4 != 0) {
        func_ov015_02072c48();
    }
    if (((PanelFlagsE1 *)(data_ov015_0207e960 + 0xe1))->flag7 != 0) {
        func_ov015_020702fc();
    }
    if (((PanelFlagsE1 *)(data_ov015_0207e960 + 0xe1))->flag3 != 0) {
        func_ov015_0206fb14();
    }
    if (((PanelFlagsE2 *)(data_ov015_0207e960 + 0xe2))->flag1 == 0) {
        return;
    }
    func_ov015_02070540();
}
